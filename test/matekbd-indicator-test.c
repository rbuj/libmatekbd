/*
 * Copyright (C) 2006 Sergey V. Udaltsov <svu@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include "libmatekbd/matekbd-indicator.h"

#include <fcntl.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef ENABLE_NLS
#include <locale.h>
#endif

#include "X11/XKBlib.h"
#include "libxklavier/xklavier.h"

int main(int argc, char** argv) {
  GtkWidget* gki;
  GtkWidget* mainwin;
  GtkWidget* vbox;

#ifdef ENABLE_NLS
  setlocale(LC_ALL, "");
  bindtextdomain(GETTEXT_PACKAGE, MATELOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);
#endif /* ENABLE_NLS */

  /* Different data dir defs in g-a and g-c-c */
  gtk_init(&argc, &argv);

  mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gki = matekbd_indicator_new();
  matekbd_indicator_set_tooltips_format(_("Keyboard Indicator Test (%s)"));
  matekbd_indicator_set_parent_tooltips(MATEKBD_INDICATOR(gki), TRUE);

  gtk_window_resize(GTK_WINDOW(mainwin), 250, 250);
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

  gtk_container_add(GTK_CONTAINER(mainwin), vbox);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 12);
  gtk_container_add(GTK_CONTAINER(vbox), gtk_label_new(_("Indicator:")));
  gtk_container_add(GTK_CONTAINER(vbox), gki);

  gtk_widget_show_all(mainwin);

  g_signal_connect(mainwin, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return EXIT_SUCCESS;
}
