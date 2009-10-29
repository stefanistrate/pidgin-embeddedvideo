#ifndef VIDEOFRAMES_H

#define VIDEOFRAMES_H

#include <glib.h>
#include <gtk/gtk.h>

#include <gtkimhtml.h>

#include "websites.h"

typedef struct _ButtonInfo ButtonInfo;

struct _ButtonInfo
{
    GtkIMHtml   *imhtml;
    GtkTextMark *mark;
    WebsiteInfo *website;
    GString     *url;
    gboolean     is_end;
};

ButtonInfo * button_info_new(GtkIMHtml *, GtkTextIter *,
        WebsiteInfo *, gchar *, gint, gboolean);
void         button_info_free(ButtonInfo *);

void         videoframes_init();
void         videoframes_destroy();
GtkWidget *  videoframes_insert_new_button(GtkIMHtml *, GtkTextIter *,
        WebsiteInfo *, gchar *, gint);
void         videoframes_remove_button(GtkWidget *);
void         videoframes_toggle_button(GtkWidget *);
gchar *      videoframes_generate_page(WebsiteInfo *, GString *);

#endif
