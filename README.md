# MATERIALES CURSO DE C MODERNO (II Edición)
Presentaciones, ejercicios y todo el material del curso hecho con latex.

## Árbol
* **raíz**
	* **\<subproyecto\>**: annexes, exercises, slides
		* **Makefile**: makefile específico para ese subproyecto
		* **src**: código latex
			* **\*.tex**: Archivos latex compartidos (clases, macros, etc)
			* **\<temas\>**: Carpetas individuales para cada tema.  Cada una genera un pdf
				* **img**: Carpeta para las imágenes de este tema
				* **csrc**: Carpeta para el código fuente de este tema (para lstinclude)
		* **[pdf]**: Carpeta autogenerada con los *.pdf del subproyecto
	* **[pdfs]**: Carpeta autogenerada dónde se guardan los *.pdf de todos los subproyectos
	* **Makefile**: Makefile general. Autogenera todos los subproyectos y guarda los *.pdf en subcarpetas dentro de la carpeta pdfs
	* **Makefile.latex**: Makefile genérico para compilar el código latex de un subproyecto

## Utilización
Compilar slides en modo presentación, ejercicios y anexos:

	raíz $> make

Compilar un subproyecto en particular:

	raíz $> make sprint # slides preparadas para ser impresas

Compilar todo:

	raíz $> make all

Trabajar dentro de un subproyecto específico:

	raíz $> cd slides
	raíz/slides $> make alum # Compila slides sin notas y las guarda en raíz/slides/pdf

## Sobre LaTeX
### Presentaciones y anexos
En el archivo _mybeamer.cls_ (duplicado en _annexes/_ y _slides/_) se cargan y
configuran los paquetes necesarios para crear las presentaciones. Los más
importantes son
**[Beamer](http://ctan.org/pkg/beamer)** (para crear las presentaciones) y
**[Listings](http://ctan.org/pkg/listings)** (para resaltado de sintaxis de
código)

En _macros.tex_ se incluyen algunos comandos y entornos para facilitar la
creación de los documentos:

* **Entornos** (`\begin{entorno}`, `\end{entorno}`)
	* `\begin{framesec}[Título corto para el índice]{Título}`: Para crear
	  un frame (una o más páginas) en ámbito de sección
	* `\begin{framesubsec}[Título corto para el índice]{Título}`: Para crear
	  un frame (una o más páginas) en ámbito de subsección
	* `\begin{framesubsubsec}[Título corto para el índice]{Título}`: Para
	  crear un frame (una o más páginas) en ámbito de subsubsección
	* `\ejframe[sección]{Título}`: Para crear una página con
	  la imagen de Ejercicios (slides/src/ejercicios.png) en el ámbito que
	  se le pase como parámetro: _sec_ (por defecto), _subsec_ o _subsubsec_
* **Comandos** (`\comando{parámetro}`)
	* `\ig{img/mi_img}{ancho}{alto}`: Inserta la imagen que se le pasa como
	  parámetro. Los parámetros _ancho_ y _alto_  especifican el porcentaje
	  (en tanto por 1) de la página que ocupará la imagen (manteniendo la
	  relación de aspecto). Si ancho y/o alto no se especifican
	  (`\ig{img/mi_img}{}{}`) se establecen a los valores por defecto 1 y
	  0.8 respectivamente

### Ejercicios
En el archivo _mybeamer.cls_ (duplicado en _annexes/_ y _slides/_) se cargan y
configuran los paquetes necesarios para crear los boletines de ejercicios.
También se definen algunos comandos y entornos para facilitar la creación de los
documentos:

* **Entornos** (`\begin{entorno}`, `\end{entorno}`)
	* `\begin{problem}[Título opcional]`: Entorno para crear el enunciado
	  del problema
	* `\begin{statement}`: Dentro de este entorno se debe de escribir el
	  texto del enunciado. Está diseñado para ir dentro del entrorno
	  `problem`
	* `\begin{subproblems}`: Entorno para un listado de subproblemas. Está
	  diseñado para ir dentro del entorno `problem`
	* `\begin{solution}` Para crear una solución a un problema.
	* `\begin{subsolution}` Para crear una solución a un subproblema. Por
	  cada `\subp` puede crearse un entorno `subsolution`. Pensada para ir
	  dentro del entorno `solution`. TODO: pasarlo a un comando del estilo
	  de `\subp`.

* **Comandos** (`\comando{parámetro}`)
	* `\subp`: Diseñado para ir dentro del entorno `subproblems`, funciona
	  de forma parecida al `\item` del entorno `itemize`. Detrás de cada
	  `\subp` se espera una descripción del suproblema
	* El mismo comando `ig` descrito anteriormente
