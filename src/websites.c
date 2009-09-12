#include "config.h"
#include "websites.h"

#include <glib.h>
#include <glib/gstdio.h>
#include <libxml/parser.h>

#include <debug.h>

static GList *list;

WebsiteInfo *
website_info_new(gpointer id, gpointer regex, gpointer embed)
{
    WebsiteInfo *info = g_new(WebsiteInfo, 1);

    g_assert(id != NULL);
    info->id = g_string_new(id);

    g_assert(regex != NULL);
    info->regex = g_regex_new(regex, 0, 0, NULL);

    g_assert(embed != NULL);
    info->embed = g_string_new(embed);

    return info;
}

void
website_info_free(gpointer data, gpointer user_data)
{
    WebsiteInfo *info = (WebsiteInfo *) data;
    g_string_free(info->id, TRUE);
    g_regex_unref(info->regex);
    g_string_free(info->embed, TRUE);
    g_free(info);
}

void
websites_init(char *path)
{
    /* Set up a new list for storing websites information. */
    list = NULL;

    /* Given the plugin path, build the path for the directory containing
       configuration files for websites. */
    GString *dirpath = g_string_new(path);
    g_string_truncate(dirpath, dirpath->len - 16); /* remove "embeddedvideo.so" */
    g_string_append(dirpath, "embeddedvideo/websites/");
    int base_length = dirpath->len;

    /* Explore the folder for XML files. */
    GDir *dir = g_dir_open(dirpath->str, 0, NULL);
    const gchar *filename = g_dir_read_name(dir);
    while (filename != NULL) {
        g_string_append(dirpath, filename);

        list = g_list_append(list, extractXmlData(dirpath->str));
        purple_debug_info(PLUGIN_ID, "Successful loading of the XML file: %s\n", dirpath->str);

        g_string_truncate(dirpath, base_length);
        filename = g_dir_read_name(dir);
    }

    /* Deallocate some resources. */
    g_dir_close(dir);
    g_string_free(dirpath, TRUE);
}

void
websites_destroy()
{
    /* Free up the memory used by the websites list. */
    g_list_foreach(list, website_info_free, NULL);
    g_list_free(list);
}

WebsiteInfo *
websites_find_match(gchar *text, gint length)
{
    WebsiteInfo *ans = NULL;
    gchar *link = g_utf8_strdown(text, length);

    /* Search for a match in the websites list. */
    GList *w;
    for (w = list; w != NULL; w = w->next) {
        if (g_regex_match(((WebsiteInfo *) w->data)->regex, link, 0, NULL)) {
            ans = (WebsiteInfo *) w->data;
            break;
        }
    }

    g_free(link);

    return ans;
}

WebsiteInfo *
extractXmlData(gchar *filename)
{
    xmlDocPtr doc = xmlParseFile(filename);
    g_assert(doc != NULL);

    xmlNodePtr node = xmlDocGetRootElement(doc);
    g_assert(node != NULL);

    xmlChar *id = NULL, *regex = NULL, *embed = NULL;

    node = node->xmlChildrenNode;
    while (node != NULL) {

        if (node->type == XML_ELEMENT_NODE) {

            xmlNodePtr value = node->xmlChildrenNode;
            xmlChar *content = NULL;

            while (value != NULL) {
                if (value->type == XML_TEXT_NODE) {
                    content = value->content;
                    break;
                }
                value = value->next;
            }

            if (!xmlStrcmp(node->name, (const xmlChar *) "id"))
                id = content;
            else if (!xmlStrcmp(node->name, (const xmlChar *) "regex"))
                regex = content;
            else if (!xmlStrcmp(node->name, (const xmlChar *) "embed"))
                embed = content;

        }

        node = node->next;

    }

    WebsiteInfo *info = website_info_new(id, regex, embed);
    xmlFreeDoc(doc);

    return info;
}
