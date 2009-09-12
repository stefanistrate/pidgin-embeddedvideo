#ifndef WEBSITES_H

#define WEBSITES_H

#include <glib.h>

typedef struct _WebsiteInfo WebsiteInfo;

struct _WebsiteInfo
{
    GString *id;
    GRegex  *regex;
    GString *embed;
};

WebsiteInfo *   website_info_new(gpointer, gpointer, gpointer);
void            website_info_free(gpointer, gpointer);

void            websites_init(char *);
void            websites_destroy();
WebsiteInfo *   websites_find_match(gchar *, gint);

WebsiteInfo *   extractXmlData(gchar *);

#endif
