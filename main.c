#include <gtk-2.0/gtk/gtk.h>

// no he cambiado la imagen del titulo porque no me gusta como se ve :P

/**
 * Area funcional (R)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * La ficha de cada jugador se infiere de su índice.
 */
typedef struct def_jugador {
  char nombre[256];
  char esCPU;
} JUGADOR;

/**
 * Estado o "judada"
 * Formato: "XXOXXOXOO"
 */
typedef struct def_estado {
  char val[9];
  struct def_estado *sigiente;
  struct def_estado *anterior;
} ESTADO;

typedef struct def_juego {
  GtkWidget *botones[9];
  void *gstructArr[9];
  char tablero[9];
  ESTADO *inicio;
  JUGADOR jugadores[2];
  int jugadorActual;

  GtkWidget *playingImg; // <-- L
  GtkWidget *playingBox; // <-- L
} JUEGO;

/**
 * Argumento del callback de los botones
 * del tablero
 *
 * Cuando presionas un botón, manda esta
 * estructura, con el id del botón que
 * se presionó.
 *
 * Cuando la ia tira, cambia el valor de
 * id al botón que quiere presionar y
 * vuelve a llamar la función de cuando
 * se presiona un botón.
 */
typedef struct def_gstruct {
  JUEGO *juego;
  GtkWidget *image; // <-- L
  int id;
} GSTRUCT;

void initJuego(JUEGO *juego);

/**
 * Fin area funcional
*/

void button_pressed(GtkWidget *eventbox, GdkEventButton *event, gpointer data);
void button_hover(GtkWidget *eventbox, GdkEventButton *event, gpointer data);
void button_leave(GtkWidget *eventbox, GdkEventButton *event, gpointer data);

void StopTheApp(GtkWidget *window, gpointer data);

int main(int argc, char *argv[])
{
    // ventana principal
    GtkWidget *window, *mainBox;

    // contenedores genericos
    GtkWidget *hBox, *hBox1, *vBox, *vBox1, *eventbox;
    GtkWidget *label, *button, *image;

    // para el menu
    GtkWidget *menuBar, *menuItem, *submenu, *subItem;
    GtkAccelGroup *group;

    // para el tablero
    GtkWidget *gameBox;

    // elemento de color
    GdkColor color;

    // imagenes customizables
    GdkPixbuf *pix;
    GError *error = NULL;

    // partida
    JUEGO juego;
    GSTRUCT *buttonData;

    initJuego(&juego);
    // populateButtonArray(&juego, verticalbox);

    // contadores
    int i = 0;
    int j = 0;

    // inicia gtk
    gtk_init(&argc, &argv);

    // obtiene un color
    gdk_color_parse("#7a7a7a", &color);

    // crea una ventana con el titulo y le asocia la función destruir
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
        gtk_container_set_border_width(GTK_CONTAINER(window), 0);
        gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe 2");
        gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(StopTheApp), &juego);

    // crea la caja que va a contener todos los elementos
    mainBox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), mainBox);

    /**
     * Sección del menú
    */

    // crea un grupo para combinaciones de teclas y lo mete a la ventana
    group = gtk_accel_group_new();
        gtk_window_add_accel_group(GTK_WINDOW(window), group);

    // crea una barra de menu y la mete a la caja principal
    menuBar = gtk_menu_bar_new();
        gtk_box_pack_start(GTK_BOX(mainBox), menuBar, FALSE, TRUE, 0);

    // crea una opcion del menu y la asocia al menu
    menuItem = gtk_image_menu_item_new();
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuItem), gtk_image_new_from_stock(GTK_STOCK_DIRECTORY, GTK_ICON_SIZE_LARGE_TOOLBAR));
        gtk_menu_item_set_label(GTK_MENU_ITEM(menuItem), "Archivo");
        gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

    // crea un submenu para la opcion y le asocia el grupo de combinaciones de teclas
    submenu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), submenu);
        gtk_menu_set_accel_group(GTK_MENU(submenu), group);

    // crea una subopción y le agrega una combinación de teclas
    subItem = gtk_menu_item_new_with_mnemonic("Guardar");
        gtk_widget_add_accelerator(subItem, "activate", group, 'S', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL); <-- asociar función respectiva (yo lo hago)
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

    // crea una subopción y le agrega una combinación de teclas
    subItem = gtk_menu_item_new_with_mnemonic("Abrir");
        gtk_widget_add_accelerator(subItem, "activate", group, 'O', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL); <-- asociar función respectiva (yo lo hago)
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);
    
    // lo mimso 2 veces

    menuItem = gtk_image_menu_item_new();
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuItem), gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_LARGE_TOOLBAR));
        gtk_menu_item_set_label(GTK_MENU_ITEM(menuItem), "Juego");
        gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

    submenu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), submenu);
        gtk_menu_set_accel_group(GTK_MENU(submenu), group);

    subItem = gtk_menu_item_new_with_mnemonic("Nuevo");
        gtk_widget_add_accelerator(subItem, "activate", group, 'N', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL);
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

    subItem = gtk_menu_item_new_with_mnemonic("Terminar");
        gtk_widget_add_accelerator(subItem, "activate", group, 'F', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL);
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);


    menuItem = gtk_image_menu_item_new();
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuItem), gtk_image_new_from_stock(GTK_STOCK_INFO, GTK_ICON_SIZE_LARGE_TOOLBAR));
        gtk_menu_item_set_label(GTK_MENU_ITEM(menuItem), "Mas");
        gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

    submenu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), submenu);
        gtk_menu_set_accel_group(GTK_MENU(submenu), group);

    subItem = gtk_menu_item_new_with_mnemonic("Como jugar");
        gtk_widget_add_accelerator(subItem, "activate", group, 'H', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL);
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

    subItem = gtk_menu_item_new_with_mnemonic("Acerca de");
        gtk_widget_add_accelerator(subItem, "activate", group, 'A', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
        // gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(optionSelected), NULL);
        gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

    /**
     * Fin de la seccion del menu
    */

    /**
     * Sección del título
    */
    // crea una caja para contener una imagen
    vBox = gtk_vbox_new(TRUE, 0);
    image = gtk_image_new_from_file("./MEDIA/title.gif");
        gtk_box_pack_start(GTK_BOX(vBox), image, TRUE, TRUE, 20);
    
    // crea una caja para contener el titulo y la mete a la ventana
    eventbox = gtk_event_box_new();
        gtk_box_pack_start(GTK_BOX(mainBox), eventbox, FALSE, TRUE, 0);
        gtk_container_add(GTK_CONTAINER(eventbox), vBox);
        gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &color);
    /**
     * Fin de la seción del título
    */

    /**
     * Sección del juego
    */

    // caja horizontal que contriene las 3 secciones de la partifa (turno actual, tablero, jugadores)
    hBox1 = gtk_hbox_new(TRUE, 10);
        gtk_box_pack_start(GTK_BOX(mainBox), hBox1, TRUE, TRUE, 10);
    
    // caja de turno actual (como se modifica la metí a la estructura de juego)
    juego.playingBox = gtk_vbox_new(FALSE, 10);
        gtk_box_pack_start(GTK_BOX(hBox1), juego.playingBox, TRUE, TRUE, 0);

    // etiqueta de la sección
    label = gtk_label_new("Jugando:");
        gtk_box_pack_start(GTK_BOX(juego.playingBox), label, FALSE, TRUE, 0);

    // imagen de jugador actual
    pix = gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("./MEDIA/x.png", &error), 20, 20, GDK_INTERP_BILINEAR);

    // asocia la imagen a la estructura del juego
    juego.playingImg = gtk_image_new_from_pixbuf(pix);
        gtk_box_pack_start(GTK_BOX(juego.playingBox), juego.playingImg, FALSE, TRUE, 0);

    // tablero
    vBox1 = gtk_vbox_new(FALSE, 10);
        gtk_box_pack_start(GTK_BOX(hBox1), vBox1, TRUE, TRUE, 0);

    // crea una caja vertical con espacio de los elementos de 5px
    vBox = gtk_vbox_new(TRUE, 5);

    // crea una caja para contener el tablero y la mete a la ventana, le mete a la caja del tablero una caja vertical
    gameBox = gtk_event_box_new();
        gtk_box_pack_start(GTK_BOX(vBox1), gameBox, TRUE, TRUE, 0);
        gtk_container_add(GTK_CONTAINER(gameBox), vBox);
        gtk_widget_modify_bg(gameBox, GTK_STATE_NORMAL, &color);
    
    // crea 3 filas de botones
    for(i = 0; i < 3; i++)
    {
        // crea una caja horizontal con espacio de los elementos de 5px y la mete a la caja vertical
        hBox = gtk_hbox_new(TRUE, 5);
            gtk_box_pack_start(GTK_BOX(vBox), hBox, TRUE, TRUE, 0);

        // crea 3 botones
        for(j = 0; j < 3; j++)
        {
            // establece una imagen transparente
            pix = gdk_pixbuf_new_from_file("./MEDIA/blank.png", &error);
            pix = gdk_pixbuf_scale_simple(pix, 40, 40, GDK_INTERP_BILINEAR);
            image = gtk_image_new_from_pixbuf(pix);

            // le da la info del botón a la estructura
            buttonData = (GSTRUCT *) juego.gstructArr[(i * 3) + j];
            buttonData->juego = &juego;
            buttonData->image = image;
            buttonData->id = (i * 3) + j;

            juego.botones[(i * 3) + j] = eventbox;

            // crea una caja de eventos y le asocia diversos eventos para estilos
            eventbox = gtk_event_box_new();
                g_signal_connect(G_OBJECT(eventbox), "button_press_event", G_CALLBACK(button_pressed), buttonData);
                g_signal_connect(G_OBJECT(eventbox), "enter-notify-event", G_CALLBACK(button_hover), buttonData);
                g_signal_connect(G_OBJECT(eventbox), "leave-notify-event", G_CALLBACK(button_leave), buttonData);
                gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox), TRUE);
                
                // le mete la imagen
                gtk_container_add(GTK_CONTAINER(eventbox), image);

            // mete la caja de eventos a la caja horizontal
            gtk_box_pack_start(GTK_BOX(hBox), eventbox, TRUE, TRUE, 0);
        }
    }

    // Sección de botones de antes y después
    hBox = gtk_hbox_new(TRUE, 10);
        gtk_box_pack_start(GTK_BOX(vBox1), hBox, FALSE, TRUE, 10);

    // crea los dos botones
    button = gtk_button_new();
        gtk_box_pack_start(GTK_BOX(hBox), button, FALSE, TRUE, 0);
        gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(GTK_STOCK_GO_BACK, GTK_ICON_SIZE_BUTTON));

    button = gtk_button_new();
        gtk_box_pack_start(GTK_BOX(hBox), button, FALSE, TRUE, 0);
        gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(GTK_STOCK_GO_FORWARD, GTK_ICON_SIZE_BUTTON));

    
    // sección de jugadores
    vBox1 = gtk_vbox_new(FALSE, 10);
        gtk_box_pack_start(GTK_BOX(hBox1), vBox1, TRUE, TRUE, 0);
    
    // titulo
    label = gtk_label_new("Jugadores:");
        gtk_box_pack_start(GTK_BOX(vBox1), label, FALSE, TRUE, 0);

    // imagen y nombre del jugador X
    pix = gdk_pixbuf_new_from_file("./MEDIA/x.png", &error);
    pix = gdk_pixbuf_scale_simple(pix, 20, 20, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(pix);
        gtk_box_pack_start(GTK_BOX(vBox1), image, FALSE, TRUE, 0);

    // imagen y nombre del jugador O
    pix = gdk_pixbuf_new_from_file("./MEDIA/o.png", &error);
    pix = gdk_pixbuf_scale_simple(pix, 20, 20, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(pix);
        gtk_box_pack_start(GTK_BOX(vBox1), image, FALSE, TRUE, 0);


    // muestra los widgets
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void StopTheApp(GtkWidget *window, gpointer data)
{
    JUEGO *juego;
    int i = 0;
  
    juego = (JUEGO *) data;

    for (i = 0; i < 9; i++) 
    {
        free(juego->gstructArr[i]);
    }

    gtk_main_quit();

    return;
}

void button_pressed(GtkWidget *eventbox, GdkEventButton *event, gpointer data)
{
    GSTRUCT *buttondata = (GSTRUCT *) data;

    GdkPixbuf *pix;
    GError *error = NULL;

    char imageSource[14];
    char players[] = "xo";

    // solo actua si está vacío el espacio
    if(buttondata->juego->tablero[buttondata->id] == ' ')
    {
        // cambia el valor en el arreglo
        buttondata->juego->tablero[buttondata->id] = players[buttondata->juego->jugadorActual];

        // carga la imagen correspondiente y la coloca en el espacio del juego
        sprintf(imageSource, "./MEDIA/%c.png", players[buttondata->juego->jugadorActual]);

        gtk_widget_destroy(buttondata->image);

        pix = gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file(imageSource, &error), 40, 40, GDK_INTERP_BILINEAR);
        buttondata->image = gtk_image_new_from_pixbuf(pix);

        gtk_container_add(GTK_CONTAINER(eventbox), buttondata->image);

        gtk_widget_show(buttondata->image);
        
        // cambia el jugador
        buttondata->juego->jugadorActual = (buttondata->juego->jugadorActual + 1) % 2;
        // cambia la imagen del turno
        sprintf(imageSource, "./MEDIA/%c.png", players[buttondata->juego->jugadorActual]);

        gtk_widget_destroy(buttondata->juego->playingImg);

        pix = gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file(imageSource, &error), 20, 20, GDK_INTERP_BILINEAR);
        buttondata->juego->playingImg = gtk_image_new_from_pixbuf(pix);

        gtk_box_pack_start(GTK_BOX(buttondata->juego->playingBox), buttondata->juego->playingImg, FALSE, TRUE, 0);
        
        gtk_widget_show(buttondata->juego->playingImg);

	// TODO: checar si alguien ganó


    }

    return;
}

void button_hover(GtkWidget *eventbox, GdkEventButton *event, gpointer data)
{
    GSTRUCT *buttondata = (GSTRUCT *) data;
    GdkColor color;

    if(buttondata->juego->tablero[buttondata->id] == ' ')
    {
        gdk_color_parse("#A3A3A3", &color);
        gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &color);
    }

    return;
}

void button_leave(GtkWidget *eventbox, GdkEventButton *event, gpointer data)
{
    GSTRUCT *buttondata = (GSTRUCT *) data;
    GdkColor color;

    if(buttondata->juego->tablero[buttondata->id] == ' ')
    {
        gdk_color_parse("#DCDAD5", &color);
        gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &color);
    }

    return;
}

void initJuego(JUEGO *juego) 
{
    int i = 0;
    char strBuffer[64];

    for (i = 0; i < 9; i++) {
        juego->gstructArr[i] = (void *) malloc(sizeof(GSTRUCT));
    }

    for (i = 0; i < 9; i++) {
        juego->tablero[i] = ' ';
    }

    juego->inicio = NULL;

    for (i = 0; i < 2; i++) {
        sprintf(strBuffer, "Jugador No.%d", i);
        strcpy(juego->jugadores[i].nombre, strBuffer);
        juego->jugadores[i].esCPU = 0;
    }

    juego->jugadorActual = 0;

    return;
}
