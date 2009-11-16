#ifndef WEBSITES_H

#define WEBSITES_H

#include <glib.h>

typedef struct _WebsiteInfo WebsiteInfo;

struct _WebsiteInfo
{
    char *id;
    char *regex;
    char *embed;
    int (*check)(gchar *const);
};

void            websites_init();
void            websites_destroy();
WebsiteInfo *   websites_find_match(gchar *const, gint);

#endif
