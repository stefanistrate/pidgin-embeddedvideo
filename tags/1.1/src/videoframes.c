#include "config.h"
#include "videoframes.h"
#include "websites.h"

#include <unistd.h>
#include <string.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>

#include <gtkimhtml.h>
#include <notify.h>
#include <debug.h>

static void videoframes_toggle_button_cb(GtkWidget *);
static gboolean new_window_policy_decision_requested_cb(WebKitWebView *,
        WebKitWebFrame *, WebKitNetworkRequest *,
        WebKitWebNavigationAction *, WebKitWebPolicyDecision *,
        gpointer);
static gboolean navigation_policy_decision_requested_cb(WebKitWebView *,
        WebKitWebFrame *, WebKitNetworkRequest *,
        WebKitWebNavigationAction *, WebKitWebPolicyDecision *,
        gpointer);

static GHashTable *ht_button_info = NULL;       /* <button, button_info> */
static GHashTable *ht_button_location = NULL;   /* <button, location> */

ButtonInfo *
button_info_new(GtkIMHtml *imhtml, GtkTextIter *location,
        WebsiteInfo *website, gchar *text, gint len)
{
    ButtonInfo *info = g_new(ButtonInfo, 1);

    info->imhtml = imhtml;
    info->mark = gtk_text_buffer_create_mark(imhtml->text_buffer, NULL,
            location, TRUE);
    info->website = website;
    info->url = g_string_new_len(text, len);
    info->has_newline = FALSE;

    return info;
}

void
button_info_free(ButtonInfo *info)
{
    gtk_text_buffer_delete_mark(info->imhtml->text_buffer, info->mark);
    g_string_free(info->url, TRUE);
    g_free(info);
}

void
videoframes_init()
{
    ht_button_info = g_hash_table_new_full(g_direct_hash, g_direct_equal,
            NULL, (GDestroyNotify) button_info_free);
    ht_button_location = g_hash_table_new(g_direct_hash, g_direct_equal);
}

void
videoframes_destroy()
{
    g_hash_table_destroy(ht_button_info);
    g_hash_table_destroy(ht_button_location);
}

GtkWidget *
videoframes_insert_new_button(GtkIMHtml *imhtml, GtkTextIter *location,
        WebsiteInfo *website, gchar *text, gint len)
{
    /* Create the button. */
    GtkWidget *button = gtk_toggle_button_new();
    gtk_widget_set_name(GTK_WIDGET(button), "video-toggle-button");
    GtkWidget *image = gtk_image_new_from_icon_name("gtk-go-forward-ltr",
            GTK_ICON_SIZE_BUTTON);
    gtk_image_set_pixel_size(GTK_IMAGE(image), 16);
    gtk_rc_parse_string("style \"video-toggle-button-style\" {"
                        "   GtkButton::inner-border = {0, 0, 0, 0}"
                        "   xthickness = 0"
                        "   ythickness = 0"
                        "   engine \"pixmap\" {"
                        "       image {"
                        "           function = BOX"
                        "       }"
                        "   }"
                        "}"
                        "widget \"*video-toggle-button\" style \"video-toggle-button-style\"");
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
    g_signal_connect(G_OBJECT(button), "toggled",
            G_CALLBACK(videoframes_toggle_button_cb), NULL);
    gtk_widget_show_all(button);

    /* Add some information regarding the button. */
    g_hash_table_insert(ht_button_info, button,
            button_info_new(imhtml, location, website, text, len));
    g_hash_table_insert(ht_button_location, button, location);

    /* Insert the button into the conversation. */
    GtkTextChildAnchor *anchor = gtk_text_buffer_create_child_anchor(
            imhtml->text_buffer, location);
    gtk_text_view_add_child_at_anchor(&imhtml->text_view, button, anchor);

    return button;
}

void
videoframes_remove_button(GtkWidget *button)
{
    /* Small trick to remove the video if the toggle button is active. */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
        videoframes_toggle_button(button);

    /* Extract the information for the current button. */
    ButtonInfo *info = (ButtonInfo *) g_hash_table_lookup(ht_button_info, button);

    /* Remove the button from the conversation.
       The widget is implicitly destroyed. */
    GtkTextIter iter, next_iter;
    gtk_text_buffer_get_iter_at_mark(info->imhtml->text_buffer, &iter, info->mark);
    next_iter = iter;
    gtk_text_iter_forward_char(&next_iter);
    gtk_text_buffer_delete(info->imhtml->text_buffer, &iter, &next_iter);

    /* Remove the information attached to the former button. */
    g_hash_table_remove(ht_button_info, button);
}

static void
videoframes_toggle_button_cb(GtkWidget *button)
{
    /* Extract the information for the current button. */
    ButtonInfo *info = (ButtonInfo *) g_hash_table_lookup(ht_button_info, button);
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(info->imhtml->text_buffer, &iter, info->mark);
    gtk_text_iter_forward_char(&iter);

    /* Get the image widget within the container. */
    GList *list = gtk_container_get_children(GTK_CONTAINER(button));
    GtkImage *image = g_list_first(list)->data;
    g_list_free(list);

    /* Turn it on or off, regarding the current state. */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {

        /* Change the image. */
        gtk_image_set_from_icon_name(image, "gtk-go-down", GTK_ICON_SIZE_BUTTON);

        /* Create the web view. */
        GtkWidget *web_view = webkit_web_view_new();

        gchar *filename = videoframes_generate_page(info->website, info->url);
        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), filename);
        g_free(filename);

        g_signal_connect(web_view, "new-window-policy-decision-requested",
                G_CALLBACK(new_window_policy_decision_requested_cb), NULL);
        g_signal_connect(web_view, "navigation-policy-decision-requested",
                G_CALLBACK(navigation_policy_decision_requested_cb), NULL);
        gtk_widget_show_all(web_view);

        /* Insert the web view into the conversation. */
        gtk_text_buffer_insert(info->imhtml->text_buffer, &iter, "\n", 1);
        GtkTextChildAnchor *anchor = gtk_text_buffer_create_child_anchor(
                info->imhtml->text_buffer, &iter);
        gtk_text_view_add_child_at_anchor(&info->imhtml->text_view, web_view, anchor);
        if (info->has_newline == TRUE)
            gtk_text_buffer_insert(info->imhtml->text_buffer, &iter, "\n", 1);

    } else {

        /* Change the image. */
        gtk_image_set_from_icon_name(image, "gtk-go-forward-ltr", GTK_ICON_SIZE_BUTTON);

        /* Remove the video from the conversation.
           The web view is implicitly destroyed. */
        GtkTextIter next_iter = iter;
        gtk_text_iter_forward_chars(&next_iter, 2 + (int) info->has_newline);
        gtk_text_buffer_delete(info->imhtml->text_buffer, &iter, &next_iter);

    }
}

static gboolean new_window_policy_decision_requested_cb(WebKitWebView *web_view,
        WebKitWebFrame *frame, WebKitNetworkRequest *request,
        WebKitWebNavigationAction *navigation_action, WebKitWebPolicyDecision *policy_decision,
        gpointer user_data)
{
    const gchar *uri = webkit_network_request_get_uri(request);
    purple_notify_uri(NULL, uri);
    return TRUE;
}

static gboolean navigation_policy_decision_requested_cb(WebKitWebView *web_view,
        WebKitWebFrame *frame, WebKitNetworkRequest *request,
        WebKitWebNavigationAction *navigation_action, WebKitWebPolicyDecision *policy_decision,
        gpointer user_data)
{
    const gchar *uri = webkit_network_request_get_uri(request);
    purple_notify_uri(NULL, uri);
    return TRUE;
}

void
videoframes_toggle_button(GtkWidget *button)
{
    GtkToggleButton *toggle_button = GTK_TOGGLE_BUTTON(button);
    gtk_toggle_button_set_active(toggle_button,
            !gtk_toggle_button_get_active(toggle_button));
}

gchar *
videoframes_generate_page(WebsiteInfo *website, GString *url)
{
    GRegex *website_regex = g_regex_new(website->regex, 0, 0, NULL);
    GMatchInfo *match_info;
    gboolean match_found = g_regex_match(website_regex, url->str, 0, &match_info);
    g_assert(match_found);

    gchar *video_id = g_match_info_fetch_named(match_info, "video_id");
    gchar *misc1 = g_match_info_fetch_named(match_info, "misc1");
    gchar *misc2 = g_match_info_fetch_named(match_info, "misc2");
    GRegex *video_id_regex = g_regex_new("%VIDEO_ID%", 0, 0, NULL);
    GRegex *misc1_regex = g_regex_new("%MISC1%", 0, 0, NULL);
    GRegex *misc2_regex = g_regex_new("%MISC2%", 0, 0, NULL);

    gchar *embed, *tmp_embed;
    embed = g_regex_replace_literal(video_id_regex,
            website->embed, -1, 0,
            video_id,
            0,
            NULL);
    if (misc1 != NULL && g_strcmp0(misc1, "") != 0) {
        tmp_embed = embed;
        embed = g_regex_replace_literal(misc1_regex,
                tmp_embed, -1, 0,
                misc1,
                0,
                NULL);
        g_free(tmp_embed);

        if (misc2 != NULL && g_strcmp0(misc2, "") != 0) {
            tmp_embed = embed;
            embed = g_regex_replace_literal(misc2_regex,
                    tmp_embed, -1, 0,
                    misc2,
                    0,
                    NULL);
            g_free(tmp_embed);
        }
    }

    gchar *filename;
    gint file = g_file_open_tmp(NULL, &filename, NULL);
    ssize_t tmp = write(file, "<html>\n<head></head>\n<body>\n", 28);
    tmp = write(file, embed, strlen(embed));
    tmp = write(file, "\n</body>\n</html>", 16);
    close(file);

    purple_debug_info(PLUGIN_ID, "New video found: site = %s, id = %s.\n",
            website->id, video_id);

    g_free(embed);

    g_regex_unref(video_id_regex);
    g_regex_unref(misc1_regex);
    g_regex_unref(misc2_regex);
    g_free(video_id);
    g_free(misc1);
    g_free(misc2);

    g_match_info_free(match_info);
    g_regex_unref(website_regex);

    gchar *ret = g_new(gchar, strlen(filename) + 9);
    g_stpcpy(g_stpcpy(ret, "file:///"), filename);
    g_free(filename);

    return ret;
}

void
videoframes_text_buffer_check_newline(gpointer key, gpointer value, gpointer user_data)
{
    GtkWidget *button = (GtkWidget *) key;
    GtkTextIter *location = (GtkTextIter *) value;
    ButtonInfo *info = (ButtonInfo *) g_hash_table_lookup(ht_button_info, key);

    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(info->imhtml->text_buffer, &iter, info->mark);

    while (gtk_text_iter_forward_char(&iter)) {
        gunichar crt_unichar = gtk_text_iter_get_char(&iter);

        if (g_unichar_break_type(crt_unichar) == G_UNICODE_BREAK_LINE_FEED)
            break;

        if (g_unichar_isgraph(crt_unichar)) {
            info->has_newline = TRUE;
            break;
        }
    }

    if (purple_prefs_get_bool("/plugins/gtk/embeddedvideo/show-video")) {
        videoframes_toggle_button(button);
        gtk_text_buffer_get_end_iter(info->imhtml->text_buffer, location);
    }
}

void
videoframes_text_buffer_end_user_action_cb(GtkTextBuffer* text_buffer, gpointer user_data)
{
    g_hash_table_foreach(ht_button_location, videoframes_text_buffer_check_newline, NULL);
    g_hash_table_remove_all(ht_button_location);
}

