\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{tareas}[2009/02/11 Carlos Falgueras Homework]

\LoadClass[a4paper, 12pt]{article}
\RequirePackage[top=1in,bottom=1in,left=1in,right=1in]{geometry}

\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[spanish,es-noquoting]{babel}
\RequirePackage{fancyhdr}                    % For modify header and footer
\RequirePackage{graphicx}
\RequirePackage{listingsutf8}                % Code formatting
\spanishplainpercent                         % Solve percent overlaps
\RequirePackage{amsmath,amsfonts,amssymb,bm} % Math
\RequirePackage{textcomp}                    % Math in tex mode
\RequirePackage{xparse}                      % Optional arguments for commands
\RequirePackage{xkeyval}                     % For make todo notes "inline" by default
\RequirePackage{todonotes}                   %TODOs
%\RequirePackage[disable]{todonotes}          %TODOs
\presetkeys{todonotes}{inline}{}             % todo notes inline by default
\RequirePackage{subcaption}	% subfigures
\RequirePackage{tocloft}	% For make problems index
\RequirePackage{changepage}	% For change indentation
\RequirePackage{color}
\RequirePackage{hyperref}
\hypersetup{
	colorlinks=true,
	linkcolor=blue,
	citecolor=blue,
	filecolor=blue,
	urlcolor=blue
}

% Images
\newcommand\ig[3]{%
	\def\w{1}%
	\def\h{0.8}%
%
	\ifthenelse{\equal{#2}{}}%
	{}%
	{\def\w{#2}}%
%
	\ifthenelse{\equal{#3}{}}%
	{}%
	{\def\h{#3}}%
%
	\includegraphics[keepaspectratio, width=\w\linewidth, height=\h\textheight]{#1}%
}

\newcommand\Tema[1]{\def\@teman{#1}}
\def\nomCurso{Curso de Programación en C Moderno (II Edición)}

\setlength{\headheight}{15pt}
\lhead{\nomCurso}\chead{}\rhead{Ejercicios tema \@teman}
\lfoot{}\cfoot{\thepage}\rfoot{}
\pagestyle{fancy}

\renewcommand\maketitle{
\begin{titlepage}
	\centering
	\ig{logous}{0.2}{0.2}
	\\[1em]
	{\scshape\LARGE Curso de Programación en\\C\\Moderno \par}
	{\scshape\Large (II Edición)\par}
	\vspace{1.5cm}
	{\huge\bfseries Ejercicios tema \@teman\par}
	\vspace{2cm}
	{\large\itshape Neira Ayuso, Pablo\\Falgueras García, Carlos\par}

	\setcounter{page}{2}
\end{titlepage}
}

% LISTINGS
\definecolor{mygray}{rgb}{0.4,0.4,0.4}
\definecolor{mygreen}{rgb}{0,0.8,0.6}
\definecolor{myorange}{rgb}{1.0,0.4,0}

\lstset{
	basicstyle=\footnotesize\ttfamily\color{black},
	upquote=true,
	commentstyle=\color{mygray},
	mathescape,
	frame=single,
	numbers=left,
	numbersep=5pt,
	numberstyle=\tiny\color{mygray},
	keywordstyle=\color{blue},
	showspaces=false,
	showstringspaces=false,
	stringstyle=\color{myorange},
	tabsize=2,
	xleftmargin=15.4pt,
	xrightmargin=3.4pt
}

\lstdefinelanguage{diff}{
	morecomment=[f][\color{blue}]{@@},     % group identifier
	morecomment=[f][\color{red}]-,         % deleted lines
	morecomment=[f][\color{green}]+,       % added lines
	morecomment=[f][\color{magenta}]{---}, % Diff header lines (must appear after +,-)
	morecomment=[f][\color{magenta}]{+++},
}

%*******************%
% TABLE OF PROBLMES %
%*******************%
\newcommand\TOPName{Índice}
\newlistof[section]{problem}{pro}{\TOPName}
\newlistentry[problem]{subproblem}{pro}{2}
\newlistentry[problem]{solution}{pro}{2}
\newlistentry[solution]{subsolution}{pro}{3}

\setcounter{prodepth}{1}
\setcounter{tocdepth}{1}

\renewcommand{\thesolution}{\theproblem.S}

%**********************%
% PARAGRAPH SEPARATION %
%**********************%
%Espaciado entre párrafos
% \newlength{\parseparation}
% \setlength{\parseparation}{1.5em}  %Distancia entre párrafos por defecto
% \newcommand{\parset}[1]{\setlength{\parskip}{#1}}  %Comando para setear distancia
% \newcommand{\parreset}{\setlength{\parskip}{\parseparation}}  %Comando para dejarla como estaba
% \parreset
\setlength{\parskip}{1.5em}

%**********%
% COUNTERS %
%**********%
% \newcounter{ProblemNum}
% \newcounter{SubProblemNum}[ProblemNum]

% \renewcommand{\theProblemNum}{\arabic{ProblemNum}}
% \renewcommand{\theSubProblemNum}{\alph{SubProblemNum}}


%***********************%
% PROBLEMS ENVIRONMENTS %
%***********************%
\definecolor{boxgray}{rgb}{0.95,0.95,0.95}
\setlength{\fboxsep}{0pt}
\newsavebox{\problembox}
\NewDocumentEnvironment{problem}{o}
{
	\IfValueTF{#1}
	{\def\probTitle{#1}}
	{\def\probTitle{Ejercicio}}

	%\clearpage
	\refstepcounter{problem}
	\addcontentsline{pro}{problem}{\protect\numberline{\theproblem} \probTitle}
	\addcontentsline{toc}{problem}{\protect\numberline{\theproblem} \probTitle}

	{\noindent \Large \bfseries \probTitle} \hrulefill
	\begin{lrbox}{\problembox}
	\begin{minipage}{\columnwidth}
	\vspace{0.5em}
}
{
	\hfill\break
	\rule{\linewidth}{0.5px}
	\end{minipage}\end{lrbox}
	\colorbox{boxgray}{\usebox{\problembox}}
}

\NewDocumentEnvironment{statement}{}
{
	\indent\slshape
}
{}

\newcommand\subp{
	~\\
	\vspace{0.5em}
	\refstepcounter{subproblem}
	\addcontentsline{pro}{subproblem}{\protect\numberline{\thesubproblem} \alph{subproblem})}
	\addcontentsline{toc}{subproblem}{\protect\numberline{\thesubproblem} \alph{subproblem})}
	{\large \bfseries \alph{subproblem})}
}

\NewDocumentEnvironment{subproblems}{}
{
	\vspace{-1em}
	\begin{adjustwidth}{2cm}{}
}
{
	\end{adjustwidth}
	\vspace{-2em}
}

\NewDocumentEnvironment{solution}{}
{
	\refstepcounter{solution}
	\addcontentsline{pro}{solution}{\protect\numberline{\thesolution} Solución}
	\addcontentsline{toc}{solution}{\protect\numberline{\thesolution} Solución}


	{\noindent \Large \bfseries Solución} \\
}
{
}

\NewDocumentEnvironment{subsolution}{}
{
	\refstepcounter{subsolution}
	\addcontentsline{pro}{subsolution}{\protect\numberline{\thesubsolution} \alph{subsolution})}
	\addcontentsline{toc}{subsolution}{\protect\numberline{\thesubsolution} \alph{subsolution})}

	\begin{adjustwidth}{2cm}{}
	{\noindent \large \bfseries \alph{subsolution})}
}
{
	\end{adjustwidth}
}
