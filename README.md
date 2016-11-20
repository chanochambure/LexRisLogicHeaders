# LexRisLogicHeaders

Las Cabeceras de LexRis Logic brindan un código amigable orientado a objetos y funciones en C++ de Matemática Básica, Temporizador, Conversiones de Tipo, Encriptador, Lector de Archivos, Separador de Cadenas, Estructuras Matemáticas, Estructuras de Datos y en especial de las librerías:

Allegro v5.2.0, ENet v1.3.13 y irrKlang v1.5.0 (API)

## Instalación

Para instalar las cabeceras de LexRis Logic se cuenta con un archivo CMake en la carpeta LexRisLogic donde se encuentran los archivos.

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
    lib/    :       Archivos de Linkeo
    include/:       Cabeceras para incluir las librerías

### 3. Consideraciones

Recuerde que esta librería ya no tiene acceso a las funciones de Allegro, ENet e irrKlang, por lo que si desea usar nuestras cabeceras como parte de las librerías deberá linkear tambien cada una de las librerías.