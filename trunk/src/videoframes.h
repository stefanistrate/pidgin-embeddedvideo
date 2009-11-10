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
    GtkTextIter *iter;
    gint         insert_newline;
};

ButtonInfo * button_info_new(GtkIMHtml *, GtkTextIter *,
        WebsiteInfo *, gchar *, gint);
void         button_info_free(ButtonInfo *);

void         videoframes_init();
void         videoframes_destroy();
void         videoframes_text_buffer_check_new_line(gpointer, gpointer, gpointer);
void         videoframes_text_buffer_end_user_action_cb(GtkTextBuffer *, gpointer);
GtkWidget *  videoframes_insert_new_button(GtkIMHtml *, GtkTextIter *,
        WebsiteInfo *, gchar *, gint);
void         videoframes_remove_button(GtkWidget *);
void         videoframes_toggle_button(GtkWidget *);
gchar *      videoframes_generate_page(WebsiteInfo *, GString *);

#endif
