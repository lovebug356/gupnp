/* 
 * Copyright (C) 2007 OpenedHand Ltd.
 *
 * Author: Jorn Baayen <jorn@openedhand.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <libgupnp/gupnp-root-device.h>
#include <stdio.h>
#include <locale.h>

int
main (int argc, char **argv)
{
        GError *error;
        GUPnPContext *context;
        xmlDoc *doc;
        GUPnPRootDevice *dev;
        GMainLoop *main_loop;

        if (argc < 2) {
                fprintf (stderr, "Usage: %s DESCRIPTION_FILE\n", argv[0]);

                return 1;
        }
        
        g_thread_init (NULL);
        g_type_init ();
        setlocale (LC_ALL, "");

        error = NULL;
        context = gupnp_context_new (NULL, NULL, 0, &error);
        if (error) {
                g_error (error->message);
                g_error_free (error);

                return 1;
        }

        /* Host current directory */
        gupnp_context_host_path (context, ".", "");

        /* Parse device description file */
        doc = xmlParseFile (argv[1]);

        /* Create root device */
        dev = gupnp_root_device_new (context,
                                     doc,
                                     "/description.xml",
                                     "/");

        /* Free doc when root device is destroyed */
        g_object_weak_ref (G_OBJECT (dev), (GWeakNotify) xmlFreeDoc, doc);

        gupnp_root_device_set_available (dev, TRUE);

        main_loop = g_main_loop_new (NULL, FALSE);
        g_main_loop_run (main_loop);
        g_main_loop_unref (main_loop);

        g_object_unref (dev);
        g_object_unref (context);

        return 0;
}