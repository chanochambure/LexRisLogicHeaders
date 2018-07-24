# LexRisLogicHeaders

Las Cabeceras de LexRis Logic brindan un código amigable orientado a objetos y funciones en C++ de Matemática Básica, Temporizador, Conversiones de Tipo, Encriptador, Lector de Archivos, Separador de Cadenas, Estructuras Matemáticas, Estructuras de Datos y en especial de las librerías:

Allegro v5.2.0, ENet v1.3.13 y irrKlang v1.5.0 (API)

## Instalación v2.10

Para instalar las cabeceras de LexRis Logic se cuenta con un archivo CMake en la carpeta LexRisLogic (Directorio Raíz).

### 1. CMake en UNIX

Clone el repositorio y siga los siguientes pasos:

    cd LexRisLogic/
    mkdir build
    cd build
    cmake ..

La compilación CMake puede ser modificada mediante los siguientes parámetros:

    -DINSTALL_ALLEGRO  :         Para decidir si instalar la extensión de Allegro 5.2.0
    -DINSTALL_ENET     :         Para decidir si instalar la extensión de ENet 1.3.13
    -DINSTALL_IRRKLANG :         Para decidir si instalar la extensión de irrKlang 1.5.0

Terminada la configuración solo resta instalar:

    make
    sudo make install

Para desinstalación:

    sudo make uninstall

### 2. CMake en Windows

Para facilidad del usuario, utilizar la interfaz gráfica de CMake, dar click en configurar, seleccionar el compilador deseado (actualmente se probo en MinGW) y cambiar las opciones, en especial el prefijo de instalación.

Terminada la configuración, genere el MakeFile y compilela, si no conoce como compilar un make, puede usar el CMake para generar un proyecto de Code::Blocks - MinGW para mayor facilidad.

Terminada la compilación he instalación contara con tres carpetas en la ruta seleccionada de instalación:

    bin/    :       Archivos DLL
    lib/    :       Archivos de Enlace
    include/:       Cabeceras para incluir las librerías

## Usando LL v2.10

Para usar las cabeceras de LexRis Logic solo debe incluir la cabecera que se usara y enlazar el módulo que se este usando, por ejemplo si usa las cabeceras simples como Convert.h, StringSplitter.h o Math.h solo deberá añadir '-lLL' en opciones de enlace.

    #include<LexRisLogic/Allegro5/...>                      //Se necesita -lLL_Allegro5
    #include<LexRisLogic/ENet/...>                          //Se necesita -lLL_ENet
    #include<LexRisLogic/irrKlang/...>                      //Se necesita -lLL_irrKlang
    #include<LexRisLogic/MathStructures/...>                //Se necesita -lLL_MathStructure
    #include<LexRisLogic/DataStructures/List.h>             //Se necesita -lLL_List
    #include<LexRisLogic/DataStructures/RTree.h>            //Se necesita -lLL_RTree
    #include<LexRisLogic/DataStructures/SparseMatrix.h>     //Se necesita -lLL_SparseMatrix
    #include<LexRisLogic/*.h>                               //Se necesita -lLL

En caso de la librería irrKlang, para reproducir audio de formato MP3 o FLAC, será necesario tener el plugin ikpMP3 e ikpFlac en la ruta del proyecto.

Las Cabeceras no tienen enlace hacia las librerías de Allegro5, ENet e irrKlang por lo que si se desea usar las cabeceras junto a las librerías será necesario enlazarlas en el proyecto.

## Documentación

La documentación de uso se encuentra en el directorio de documentación como "Guía del Programador", ahí encontrará redactado la funcionalidad de cada una de las variables, funciones y clases públicas de las cabeceras de LexRis Logic.
