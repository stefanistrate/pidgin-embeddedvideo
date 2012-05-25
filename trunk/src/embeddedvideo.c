#define PURPLE_PLUGINS

#include "config.h"
#include "websites.h"
#include "videoframes.h"

#include <glib.h>

/* Pidgin headers */
#include <plugin.h>
#include <gtkplugin.h>
#include <gtkconv.h>
#include <gtkimhtml.h>
#include <pluginpref.h>
#include <prefs.h>
#include <version.h>
#include <debug.h>

static GHashTable *ht_buttons = NULL;               /* <button, imhtml> */
static GHashTable *ht_signal_handlers_it = NULL;    /* <text_buffer, "insert-text"> */
static GHashTable *ht_signal_handlers_eua = NULL;   /* <text_buffer, "end-user-action"> */

static void
insert_text_cb(GtkTextBuffer *textbuffer, GtkTextIter *location,
        gchar *text, gint len, gpointer user_data)
{
    GtkIMHtml *imhtml = GTK_IMHTML(user_data);
    g_assert(GTK_IS_IMHTML(imhtml));

    if (imhtml->edit.link != NULL) {

        WebsiteInfo *info = websites_find_match(text, len);
        if (info == NULL)
            return;

        imhtml->edit.link = NULL;

        GtkWidget *button = videoframes_insert_new_button(imhtml, location, info, text, len);
        g_hash_table_insert(ht_buttons, button, imhtml);

        gtk_text_buffer_get_end_iter(imhtml->text_buffer, location);

    }
}

static void
attach_to_conversation(gpointer data, gpointer user_data)
{
    PurpleConversation *conv = (PurpleConversation *) data;
    PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);

    GtkIMHtml *imhtml = GTK_IMHTML(gtkconv->imhtml);
    g_assert(GTK_IS_IMHTML(imhtml));

    gulong handler_id = g_signal_connect_after(G_OBJECT(imhtml->text_buffer),
            "insert-text", G_CALLBACK(insert_text_cb), imhtml);
    g_hash_table_insert(ht_signal_handlers_it, imhtml->text_buffer, (gpointer) handler_id);

    handler_id = g_signal_connect(G_OBJECT(imhtml->text_buffer),
            "end-user-action", G_CALLBACK(videoframes_text_buffer_end_user_action_cb), NULL);
    g_hash_table_insert(ht_signal_handlers_eua, imhtml->text_buffer, (gpointer) handler_id);
}

static void
detach_from_conversation(gpointer data, gpointer user_data)
{
    PurpleConversation *conv = (PurpleConversation *) data;
    PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);

    GtkIMHtml *imhtml = GTK_IMHTML(gtkconv->imhtml);
    g_assert(GTK_IS_IMHTML(imhtml));

    gulong handler_id = (gulong) g_hash_table_lookup(ht_signal_handlers_it,
            imhtml->text_buffer);
    g_signal_handler_disconnect(imhtml->text_buffer, handler_id);
    g_hash_table_remove(ht_signal_handlers_it, imhtml->text_buffer);

    handler_id = (gulong) g_hash_table_lookup(ht_signal_handlers_eua,
            imhtml->text_buffer);
    g_signal_handler_disconnect(imhtml->text_buffer, handler_id);
    g_hash_table_remove(ht_signal_handlers_eua, imhtml->text_buffer);
}

static void
conversation_created_cb(PurpleConversation *conv)
{
    attach_to_conversation(conv, NULL);
}

static gboolean
deleting_conversation_remove_button(gpointer key, gpointer value,
        gpointer user_data)
{
    return (value == user_data) ? TRUE : FALSE;
}

static void
deleting_conversation_cb(PurpleConversation *conv)
{
    detach_from_conversation(conv, NULL);

    g_hash_table_foreach_remove(ht_buttons, deleting_conversation_remove_button,
            PIDGIN_CONVERSATION(conv)->imhtml);
}

static gboolean
plugin_load(PurplePlugin *plugin)
{
    /* Load websites rules. */
    websites_init();

    /* Do some more initializations. */
    videoframes_init();

    /* Create the hash table for buttons. */
    ht_buttons = g_hash_table_new_full(g_direct_hash, g_direct_equal,
            (GDestroyNotify) videoframes_remove_button, NULL);

    /* Create the hash tables for signal handlers. */
    ht_signal_handlers_it = g_hash_table_new(g_direct_hash, g_direct_equal);
    ht_signal_handlers_eua = g_hash_table_new(g_direct_hash, g_direct_equal);

    /* Attach to current conversations. */
    g_list_foreach(purple_get_conversations(), attach_to_conversation, NULL);

    /* Connect signals for future conversations. */
    void *conv_handle = purple_conversations_get_handle();
    purple_signal_connect(conv_handle, "conversation-created", plugin,
            PURPLE_CALLBACK(conversation_created_cb), NULL);
    purple_signal_connect(conv_handle, "deleting-conversation", plugin,
            PURPLE_CALLBACK(deleting_conversation_cb), NULL);

    return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin)
{
    /* Disconnect signals for future conversations. */
    void *conv_handle = purple_conversations_get_handle();
    purple_signal_disconnect(conv_handle, "conversation-created", plugin,
            PURPLE_CALLBACK(conversation_created_cb));
    purple_signal_disconnect(conv_handle, "deleting-conversation", plugin,
            PURPLE_CALLBACK(deleting_conversation_cb));

    /* Detach from current conversations. */
    g_list_foreach(purple_get_conversations(), detach_from_conversation, NULL);

    /* Destroy the hash tables for signal handlers. */
    g_hash_table_destroy(ht_signal_handlers_it);
    g_hash_table_destroy(ht_signal_handlers_eua);

    /* Remove all the inserted buttons and destroy the hash table.
       Every button will automatically remove its video frame if it has one. */
    g_hash_table_destroy(ht_buttons);

    /* Free up some resources. */
    videoframes_destroy();

    /* Unload websites rules. */
    websites_destroy();

    return TRUE;
}

static PurplePluginPrefFrame *
get_plugin_pref_frame(PurplePlugin *plugin)
{
    PurplePluginPrefFrame *frame;
    PurplePluginPref *ppref;

    frame = purple_plugin_pref_frame_new();

    ppref = purple_plugin_pref_new_with_label("Appearance");
    purple_plugin_pref_frame_add(frame, ppref);

    ppref = purple_plugin_pref_new_with_name_and_label(
            "/plugins/gtk/embeddedvideo/show-video",
            "Show every video instantly"
            );
    purple_plugin_pref_frame_add(frame, ppref);

    return frame;
}

static PurplePluginUiInfo prefs_info = {
    get_plugin_pref_frame,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    PIDGIN_PLUGIN_TYPE,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    PLUGIN_ID,
    "Pidgin Embedded Video",
    "1.2",
    "Watch videos directly into the conversation.",
    "This plugin provides you an easy way to watch videos from popular websites"
        " (CollegeHumor, Dailymotion, Google Video, Metacafe, MySpace Video,"
        " Trilulilu, Vimeo, Xfire, Yahoo! Video and Youtube) directly into the"
        " conversation. Send and receive links and the plugin will insert the"
        " video.",
    "Ștefan Istrate <stefan.istrate@gmail.com>\n"
        "Marius Stroe <laurentiu.stroe@gmail.com>",
    "http://code.google.com/p/pidgin-embeddedvideo/",

    plugin_load,
    plugin_unload,
    NULL,

    NULL,
    NULL,
    &prefs_info,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static void
init_plugin(PurplePlugin *plugin)
{
    purple_prefs_add_none("/plugins/gtk/embeddedvideo");
    purple_prefs_add_bool("/plugins/gtk/embeddedvideo/show-video", TRUE);
}

PURPLE_INIT_PLUGIN(embeddedvideo, init_plugin, info)
