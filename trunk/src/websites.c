#include "config.h"
#include "websites.h"

#include <glib.h>

#include <debug.h>

static GList *list;

void
websites_init()
{
    /* Extern declarations. */
    extern WebsiteInfo  trilulilu_audio,
                        trilulilu_image,
                        trilulilu_video,
                        vimeo,
                        youtube;

    /* Initialize the websites list. */
    list = NULL;
    list = g_list_append(list, &trilulilu_audio);
    list = g_list_append(list, &trilulilu_image);
    list = g_list_append(list, &trilulilu_video);
    list = g_list_append(list, &vimeo);
    list = g_list_append(list, &youtube);
}

void
websites_destroy()
{
    /* Empty the websites list. */
    g_list_free(list);
}

WebsiteInfo *
websites_find_match(gchar *const text, gint length)
{
    WebsiteInfo *ans = NULL;
    gchar *link = g_new0(gchar, length + 1);
    g_utf8_strncpy(link, text, length);

    /* Search for a match in the websites list. */
    GList *w;
    for (w = list; w != NULL; w = w->next) {
        if (g_regex_match_simple(((WebsiteInfo *) w->data)->regex, link, 0, 0)) {
            if (((WebsiteInfo *) w->data)->check == NULL ||
                    (*((WebsiteInfo *) w->data)->check)(link)) {
                ans = (WebsiteInfo *) w->data;
                break;
            }
        }
    }

    g_free(link);

    return ans;
}
