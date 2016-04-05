\LoadClass[beamer]{beamer}            % only frames
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{mybeamer}[2016/03/15 My custom beamer class]

% PACKAGES
% Idiom and codification
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[spanish,es-noquoting]{babel}

\RequirePackage{hyperref}
\RequirePackage{url}
\RequirePackage{listingsutf8}                % Code formatting
\spanishplainpercent                         % Solve percent overlaps
\RequirePackage{color}                       % Colors for code
\RequirePackage{xkeyval}                     % For make todo notes "inline" by default
\RequirePackage{todonotes}                   %TODOs
%\RequirePackage[disable]{todonotes}          %TODOs
\presetkeys{todonotes}{inline}{}             % todo notes inline by default
\RequirePackage{graphicx}                    % Images
\RequirePackage{amsmath,amsfonts,amssymb,bm} % Math
\RequirePackage{textcomp}                    % Math in tex mode
\RequirePackage{pgfpages}
\RequirePackage{xparse}                      % Optional arguments for commands
\RequirePackage{environ}                     % For xparse nesting fix
\RequirePackage{xstring}                     % For switch-case with strings
\RequirePackage{multicol}
\RequirePackage[normalem]{ulem}              % For cross text


% PRESENTATION DATA
\title[Portada]{Curso de programación en C moderno}
\subtitle{(II Edición)}

\author[]{Neira Ayuso, Pablo \and Falgueras García, Carlos}
\date{}

% PRESENTATION CONFIG
%\usetheme{Hannover}
\usetheme{Berkeley}
\usecolortheme{seahorse}
\logo{\includegraphics[scale=0.08]{logous}}

\mode<beamer> {
	\setbeameroption{show notes on second screen=right}  % <4sed:show notes>
}

\mode<handout> {
	\setbeamercolor{background canvas}{bg=white}
	\setbeamercolor{structure}{fg=white}
	\setbeamercolor{section in sidebar}{fg=black}
	\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]
}
\setbeamertemplate{itemize items}[circle]


% Links and PDF attributes
\hypersetup{
	colorlinks=true,
	linkcolor=blue,
	citecolor=blue,
	filecolor=blue,
	urlcolor=blue
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
	breaklines=true,
	tabsize=2
}

\lstdefinelanguage{diff}{
	morecomment=[f][\color{blue}]{@@},     % group identifier
	morecomment=[f][\color{red}]-,         % deleted lines
	morecomment=[f][\color{green}]+,       % added lines
	morecomment=[f][\color{magenta}]{---}, % Diff header lines (must appear after +,-)
	morecomment=[f][\color{magenta}]{+++},
}

\include{macros}
