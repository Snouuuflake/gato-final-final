#include "header.h"

void loadMainWindow(JUEGO *juego)
{
  // ventana principal
  GtkWidget *mainBox;

  // contenedores genericos
  GtkWidget *hBox, *hBox1, *vBox, *vBox1, *eventbox;
  GtkWidget *label, *image;

  // para el menu
  GtkWidget *menuBar, *menuItem, *submenu, *subItem;
  GtkAccelGroup *group;

  // elemento de color
  GdkColor color;

  GSTRUCT *buttonData;

  // contadores
  int i = 0;
  int j = 0;

  // creación de elementos que se usan más de una vez
  gdk_color_parse("#7a7a7a", &color);

  juego->graficos.m20[0] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/x.png", 20, 20, TRUE, NULL);
  juego->graficos.m20[1] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/o.png", 20, 20, TRUE, NULL);
  juego->graficos.m20[2] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/blank.png", 20, 20, TRUE, NULL);
  
  juego->graficos.m40[0] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/x.png", 40, 40, TRUE, NULL);
  juego->graficos.m40[1] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/o.png", 40, 40, TRUE, NULL);
  juego->graficos.m40[2] = gdk_pixbuf_new_from_file_at_scale("./MEDIA/blank.png", 40, 40, TRUE, NULL);

  // crea una ventana con el titulo y le asocia la función destruir
  juego->graficos.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(juego->graficos.window), 600, 450);
    gtk_container_set_border_width(GTK_CONTAINER(juego->graficos.window), 0);
    gtk_window_set_title(GTK_WINDOW(juego->graficos.window), "Tic-Tac-Toe 2");
    gtk_signal_connect(GTK_OBJECT(juego->graficos.window), "destroy", GTK_SIGNAL_FUNC(StopTheApp), juego);

  // crea la caja que va a contener todos los elementos
  mainBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(juego->graficos.window), mainBox);

  /**
   * Sección del menú
   */

  // crea un grupo para combinaciones de teclas y lo mete a la ventana
  group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(juego->graficos.window), group);

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
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(guardarPartida), juego);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

  // crea una subopción y le agrega una combinación de teclas
  subItem = gtk_menu_item_new_with_mnemonic("Abrir");
    gtk_widget_add_accelerator(subItem, "activate", group, 'O', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(cargarPartida), juego);
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
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(nuevaPartida), juego);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

  subItem = gtk_menu_item_new_with_mnemonic("Terminar");
    gtk_widget_add_accelerator(subItem, "activate", group, 'F', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(terminarPartida), juego);
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
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(comoJugar), juego);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), subItem);

  subItem = gtk_menu_item_new_with_mnemonic("Acerca de");
    gtk_widget_add_accelerator(subItem, "activate", group, 'A', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_signal_connect(GTK_OBJECT(subItem), "activate", G_CALLBACK(creditos), juego);
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
    gtk_widget_modify_bg(eventbox, GTK_STATE_INSENSITIVE, &color);
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
  juego->graficos.playingBox = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hBox1), juego->graficos.playingBox, TRUE, TRUE, 0);

  // etiqueta de la sección
  label = gtk_label_new("Jugando:");
    gtk_box_pack_start(GTK_BOX(juego->graficos.playingBox), label, FALSE, TRUE, 0);

  // asocia la imagen a la estructura del juego
  juego->graficos.playingImg = gtk_image_new_from_pixbuf(juego->graficos.m40[2]);
    gtk_box_pack_start(GTK_BOX(juego->graficos.playingBox), juego->graficos.playingImg, FALSE, TRUE, 0);


  // tablero
  vBox1 = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hBox1), vBox1, TRUE, TRUE, 0);

  // crea una caja para contener el tablero y la mete a la ventana, le mete a la caja del tablero una caja vertical
  juego->graficos.board = gtk_event_box_new();
    gtk_box_pack_start(GTK_BOX(vBox1), juego->graficos.board, TRUE, TRUE, 0);
    gtk_widget_modify_bg(juego->graficos.board, GTK_STATE_NORMAL, &color);
    gtk_widget_modify_bg(juego->graficos.board, GTK_STATE_INSENSITIVE, &color);

  vBox = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(juego->graficos.board), vBox);

  // crea 3 filas de botones
  for(i = 0; i < 3; i++)
  {
    // crea una caja horizontal con espacio de los elementos de 5px y la mete a la caja vertical
    hBox = gtk_hbox_new(TRUE, 5);
      gtk_box_pack_start(GTK_BOX(vBox), hBox, TRUE, TRUE, 0);

    // crea 3 botones
    for(j = 0; j < 3; j++)
    {
      // le da la info del botón a la estructura
      buttonData = (GSTRUCT *) juego->gstructArr[(i * 3) + j];
      buttonData->juego = juego;
      buttonData->id = (i * 3) + j;

      // crea una caja de eventos y le asocia diversos eventos para estilos
      juego->botones[(i * 3) + j] = gtk_event_box_new();
        g_signal_connect(G_OBJECT(juego->botones[(i * 3) + j]), "button_press_event", G_CALLBACK(button_pressed), buttonData);
        g_signal_connect(G_OBJECT(juego->botones[(i * 3) + j]), "enter-notify-event", G_CALLBACK(button_hover), buttonData);
        g_signal_connect(G_OBJECT(juego->botones[(i * 3) + j]), "leave-notify-event", G_CALLBACK(button_leave), buttonData);
        gtk_event_box_set_above_child(GTK_EVENT_BOX(juego->botones[(i * 3) + j]), TRUE);
        gtk_box_pack_start(GTK_BOX(hBox), juego->botones[(i * 3) + j], TRUE, TRUE, 0);

      // establece una imagen transparente
      buttonData->image = gtk_image_new_from_pixbuf(juego->graficos.m40[2]);
        gtk_container_add(GTK_CONTAINER(juego->botones[(i * 3) + j]), buttonData->image);
    }
  }

  // Sección de botones de antes y después
  hBox = gtk_hbox_new(TRUE, 10);
    gtk_box_pack_start(GTK_BOX(vBox1), hBox, FALSE, TRUE, 10);

  // crea los dos botones
  juego->graficos.moveButtons[0] = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.moveButtons[0], FALSE, TRUE, 0);
    gtk_button_set_image(GTK_BUTTON(juego->graficos.moveButtons[0]), gtk_image_new_from_stock(GTK_STOCK_GO_BACK, GTK_ICON_SIZE_BUTTON));
    gtk_widget_set_sensitive(juego->graficos.moveButtons[0], FALSE);

  juego->graficos.moveButtons[1] = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.moveButtons[1], FALSE, TRUE, 0);
    gtk_button_set_image(GTK_BUTTON(juego->graficos.moveButtons[1]), gtk_image_new_from_stock(GTK_STOCK_GO_FORWARD, GTK_ICON_SIZE_BUTTON));
    gtk_widget_set_sensitive(juego->graficos.moveButtons[1], FALSE);


  // sección de jugadores
  vBox1 = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hBox1), vBox1, TRUE, TRUE, 0);

  // titulo
  label = gtk_label_new("Jugadores:");
    gtk_box_pack_start(GTK_BOX(vBox1), label, FALSE, TRUE, 0);


  // imagen y nombre del jugador X
  hBox = gtk_hbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vBox1), hBox, FALSE, TRUE, 0);

  juego->graficos.playerImg[0] = gtk_image_new_from_pixbuf(juego->graficos.m20[0]);
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.playerImg[0], FALSE, TRUE, 0);

  juego->graficos.playerName[0] = gtk_label_new("\0");
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.playerName[0], FALSE, TRUE, 0);


  // imagen y nombre del jugador O
  hBox = gtk_hbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vBox1), hBox, FALSE, TRUE, 0);

  juego->graficos.playerImg[1] = gtk_image_new_from_pixbuf(juego->graficos.m20[1]);
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.playerImg[1], FALSE, TRUE, 0);

  juego->graficos.playerName[1] = gtk_label_new("\0");
    gtk_box_pack_start(GTK_BOX(hBox), juego->graficos.playerName[1], FALSE, TRUE, 0);


  // muestra los widgets
  gtk_widget_show_all(juego->graficos.window);

  return;
}

void nuevaPartida(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;
  
  NGDATA newGame;

  GtkWidget *dialog, *mBox, *hBox, *label;

  const gchar *names[2];
  char plrnms[2][2000];

  gint res = 0;

  int s = 0;

  if(datos->estadoPartida)
  {
    g_print("Partida en curso, guardar?\n"); // <-- estos serán reemplazados por popups
  }

  dialog = gtk_dialog_new_with_buttons("Nueva partida", GTK_WINDOW(datos->graficos.window), GTK_DIALOG_MODAL, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 453, 316);
  
  mBox = gtk_vbox_new(TRUE, 10);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), mBox, TRUE, TRUE, 5);

  label = gtk_label_new("Adversario:");
    gtk_box_pack_start(GTK_BOX(mBox), label, TRUE, TRUE, 5);
  
  hBox = gtk_hbox_new(TRUE, 10);
    gtk_box_pack_start(GTK_BOX(mBox), hBox, FALSE, FALSE, 5);

  newGame.radioButtons[0] = gtk_radio_button_new_with_label(NULL, "Jugador");
    gtk_box_pack_start(GTK_BOX(hBox), newGame.radioButtons[0], TRUE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(newGame.radioButtons[0]), "toggled", G_CALLBACK(radio_changed), &newGame);

  newGame.radioButtons[1] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(newGame.radioButtons[0]), "Computadora");
    gtk_box_pack_start(GTK_BOX(hBox), newGame.radioButtons[1], TRUE, FALSE, 0);
  
  hBox = gtk_hbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(mBox), hBox, FALSE, TRUE, 0);

  newGame.chb = gtk_toggle_button_new_with_label("Modo dificil.");
    gtk_box_pack_start(GTK_BOX(hBox), newGame.chb, FALSE, TRUE, 0);
    gtk_widget_set_sensitive(newGame.chb, FALSE);
  
  label = gtk_label_new("Nombre(s):");
    gtk_box_pack_start(GTK_BOX(mBox), label, TRUE, TRUE, 0);
  
  hBox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(mBox), hBox, TRUE, TRUE, 5);
  
  label = gtk_label_new("Jugador 1:");
    gtk_box_pack_start(GTK_BOX(hBox), label, FALSE, TRUE, 5);

  newGame.players[0] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hBox), newGame.players[0], TRUE, TRUE, 5);

  hBox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(mBox), hBox, TRUE, TRUE, 5);

  label = gtk_label_new("Jugador 2:");
    gtk_box_pack_start(GTK_BOX(hBox), label, FALSE, TRUE, 5);

  newGame.players[1] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hBox), newGame.players[1], TRUE, TRUE, 5);
  
  newGame.eLabel = gtk_label_new("\0");
    gtk_box_pack_start(GTK_BOX(mBox), newGame.eLabel, TRUE, TRUE, 5);
  
  gtk_widget_show_all(dialog);
  
  do
  {
    s = 1;

    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if(res == GTK_RESPONSE_OK)
    {
      names[0] = gtk_entry_get_text(GTK_ENTRY(newGame.players[0]));
      names[1] = gtk_entry_get_text(GTK_ENTRY(newGame.players[1]));

      strcpy(plrnms[0], names[0]);
      strcpy(plrnms[1], names[1]);

      if((gtk_widget_get_sensitive(newGame.players[1]) && !strlen(names[1])) || !strlen(names[0]))
      {
        gtk_label_set_text(GTK_LABEL(newGame.eLabel), "Debes llenar todos los campos activos.");
        
        s = 0;
      }
      else if(!strcmp(names[0], names[1]))
      {
        gtk_label_set_text(GTK_LABEL(newGame.eLabel), "Los nombres no pueden ser iguales.");
        
        s = 0;
      }
      else if((!gtk_widget_get_sensitive(newGame.players[1]) && !strcmp(names[0], AI_NAME)))
      {
        gtk_label_set_text(GTK_LABEL(newGame.eLabel), "Hercules.raw, solo puede haber uno.");
        
        s = 0;
      }
      else if(gtk_widget_get_sensitive(newGame.players[1]))
      {
        restartJuego(datos, FALSE, FALSE, plrnms[0], plrnms[1]);
      }
      else
      {
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(newGame.chb)))
        {
          restartJuego(datos, TRUE, TRUE, plrnms[0], NULL);
        }
        else
        {
          restartJuego(datos, TRUE, FALSE, plrnms[0], NULL);
        }
      }
    }
    else
    {
      s = 1;
    }
  } while(!s);
  
  gtk_widget_destroy(dialog);

  return;
}

void terminarPartida(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;

  if(datos->estadoPartida)
  {
    g_print("guardar antes de terminar?\n");
  }
  else
  {
    g_print("Sin partida en curso\n");
  }

  return;
}

void guardarPartida(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;

  GtkWidget *dialog, *label, *box;

  gint result = 0;
  gchar *file;

  if(datos->estadoPartida)
  {
    dialog = gtk_file_chooser_dialog_new("Guardar Partida", GTK_WINDOW(datos->graficos.window), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if(result == GTK_RESPONSE_ACCEPT)
    {
      file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
      
      // random save function goes here
      g_print("%s\n", file);

      g_free(file);
    }

    gtk_widget_destroy(dialog);
  }
  else
  {
    dialog = gtk_dialog_new_with_buttons("No se puede guardar", GTK_WINDOW(datos->graficos.window), GTK_DIALOG_MODAL, "Cerrar", GTK_RESPONSE_CLOSE, NULL);

    box = gtk_vbox_new(TRUE, 10);
      gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), box, TRUE, TRUE, 20);
      gtk_container_set_border_width(GTK_CONTAINER(box), 10);

    label = gtk_label_new("No hay una partida en curso para guardar.");
      gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 20);
    
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);
  }

  return;
}

void cargarPartida(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;

  if(datos->estadoPartida)
  {
    g_print("Guardar partida actual?\n");
  }
  
  g_print("pantalla de carga de partida\n");

  return;
}

void comoJugar(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;

  g_print("Instructivo\n");

  return;
}

void creditos(GtkWidget *widget, gpointer data)
{
  JUEGO *datos = (JUEGO *)data;

  g_print("Creditos\n");

  return;
}