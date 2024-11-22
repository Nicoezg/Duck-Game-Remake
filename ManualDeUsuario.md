# Manual de Usuario

## 1. Instalacion de dependencias y compilacion

Para instalar las dependencias necesarias para el correcto funcionamiento del programa, se debe ejecutar el siguiente comando en la terminal:

```bash
chmod +x install_all.sh
sudo ./install_all.sh
```

Una vez esto, se debe compilar el programa. Para esto se debe ejecutar el siguiente comando en la terminal:

```bash
make
```

## 2. Ejecucion del juego

Para poder ejecutar el juego primero se va a tener que ejecutar el servidor y luego el cliente. Para ejecutar el servidor se debe ejecutar el siguiente comando en la terminal estando parados en build:

```bash
./SERVER <puerto>
```

Luego para ejecutar el cliente se debe ejecutar el siguiente comando en la terminal estando parados en build:

```bash
./CLIENT localhost <puerto>
```

Una vez hecho esto, se ejecutara y se abrira el lobby del juego.

Tambien se puede ejecutar el editor del juego, para esto se debe ejecutar el siguiente comando en la terminal estando parados en build:

```bash
./EDITOR
```

## 3. Interfaz del Lobby

En el lobby se va a poder crear una partida como unirse a una. Para crear una partida se podran hacer una configuraciones y despues una vez en el lobby de espera, el administrador de la partida podra iniciar la partida. Para unirse a una partida, se debe seleccionar una partida de la lista y luego hacer click en unirse.

## 4. Interfaz del Juego

Las mecanicas disponibles son muy acotadas pero se pueden realizar las siguientes acciones:

- Moverse con las flechas del teclado.
- Disparar con la G.
- Mirar para arriba con Y
- Hacerse el muerto con la flecha hacia abajo.

## 5. Server

Para poder cerrar el servidor se debe mandar por consola la letra q en la terminal.

## 6. Editor

El editor es una herramienta que permite crear mapas para el juego. Se pueden crear mapas de 10x10 y se pueden agregar las estructuras, cascos, cajas, armaduras y spawns.

Para agregar cualquiera de estos elementos se debe hacer click en el boton de estructura y luego hacer click en el mapa. Se pueden elegir 2 fondos, uno de un bosque y otro de un volcan. Se puede activar una goma de borrar apretando el boton eraiser y luego haciendo click en el mapa. Para volver a poner estructuras simplemente se debe volver a apretar el boton de estructura y hacer click en el mapa. Se puede borrar todo con el boton de erase.

El mapa se puede guardar con el boton de save y se puede cargar con el boton de load. Es importante que los mapas deben guardarse en el siguiente directorio: server/logic/maps y ademas debe guardarse como tipo yaml. Se puede salir del editor con el boton de exit.
