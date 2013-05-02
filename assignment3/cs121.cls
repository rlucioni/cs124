%%% Document class for CS121 documents
%%% Much of this file was stolen from psinclude.tex, which included
%%%   LaTeX code writen by Bob Walton and Craig Silverstein, and edited
%%%   at various times by Adam Deaton and Ben Wildasin.  This document
%%%   class is originally due to Robert Haas.
%%%
%%% Fall '98
%%% ========
%%%    Updated to get rid of some old dependencies (RSC)
%%%
%%% Fall '99
%%% ========
%%%    Problems with more than 26 subparts [labelled AA, BB, etc.] (RMH)
%%%    Problem sets that can't be turned in late [third arg of NONE] (RMH)
%%%    Problems worth 1 point print as (1 point) instead of (1 points) (RMH)
%%%    \smiley (RSC)
%%% 
%%% Fall '00
%%% ========
%%%    Common language functions added (\Prefix, \Suffix, etc.)  (RSC)
%%%    Indentation is now 0.25in rather than 0.00.  (RSC)
%%%
%%% Fall '01
%%% ========
%%%    Minor revisions--new problem set due date, etc. (BDC, JLK)
%%%
%%% Fall '04
%%% ========
%%%    Minor revisions to p-set header. (JRP)
%%%
%%% Fall '08
%%% ========
%%%    Minor revisions to p-set header. (PP)
%%% Fall '09
%%% ========
%%%    Minor revisions to p-set header. (VS)
%%%
%%% Fall '10
%%% ========
%%%    ps0: don't mention late days, no points per problem.
%%%    Email submission instructions (JP)
%%%    Updated header text, added new commands for student name and collaborators. Created new command subsolution to provide answer space. (MR)
%%% Fall '11
%%% ========
%%%    Modified email submission instructions (JT)


\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{cs121}[1996/11/04 1.0 (RMH)]

%%% Create some appropriately named counters.
\newcounter{Part}
\newcounter{Problem}
\newcounter{Subproblem}[Problem]   % WITHIN problem: reset when
                   % *problem* is
\newcounter{Subsolution}[Problem]
\newcounter{SubproblemX}
\newcounter{SubsolutionX}
\newcommand{\nextproblem}[1]{\setcounter{Problem}{#1}}


%%% Generic header.  This gets redefined if the 'ps' or 'solution' options
%%% are specified.
\newcommand{\header}[1]
{
   \begin{center}
   %{\large \bf Harvard University}\\
   {\large \bf Computer Science 124}\\
   {\bf Problem set by Renzo Lucioni}\\

   \medskip
   {\bf #1}
   \end{center}
}

%%% Generic header.  This version doesn't get redefined.
\newcommand{\genericheader}[1]
{
   \begin{center}
   %{\large \bf Harvard University}\\
   {\large \bf Computer Science 181}\\
   {\bf Problem set by Renzo Lucioni}\\

   \medskip
   {\bf #1}
   \end{center}
}

%%% Specify the author.
\renewcommand{\author}[1]
{
   \vspace{-0.2in}
   \begin{center}
   \it Questions and comments to #1.
   \end{center}
}

\newcommand{\printStudentName}
{
\begin{center}
   Problem set by \studentName
\end{center}
}

\newcommand{\printCollaboration} 
{
\begin{center}
Collaboration Statement: \collaborationStatement
\end{center}
}

%%% Make a "problem*" environment
\newenvironment{problem*}[1][]
{ % On entering environment.  
   \bigskip
   \begin{center}
   PROBLEM \mbox{#1}
   \end{center}
   \begin{small} 
   \begin{sf} 
   \begin{quote}
}
{ % On leaving environment.
   \end{quote}
   \end{sf}
   \end{small}
}

%%% Make a "problem" environment.
\newenvironment{problem}[0]
{ % On entering environment.
   \stepcounter{Problem}
   \begin{problem*}[\arabic{Problem}]
}
{ % On leaving environment.
   \end{problem*}
}

%%% Make a "dummy" \PART command
\newcommand{\PART}[1]
{
   \PackageError{cs121}{^^J
You have to specify the [ps] option to get the PART command}%
{Edit the first line of the source file to read documentclass[ps]{cs121}^^J
instead of just documentclass{cs121}.}
}

%%% Set up "ps" options
\DeclareOption{ps}{
   %% Set up for ps
   \renewcommand{\header}[4]         % 4 ARGUMENTS: ps #, due date, late
   {                     % date, late percent off
    \setlength{\parskip}{0.0in}      % Use late date NONE for no lateness.
    \begin{center}
   %{\large \bf Harvard University}\\
   {\large \bf Computer Science 181}\\
   {\bf Writeup by Renzo Lucioni}\\
   
    \medskip
    {\bf Assignment #1}\\
   
    \medskip
    {\sf Due #2 at 11:59 PM.\\
 Submit your solutions electronically on the course website, located at \url{http://people.seas.harvard.edu/~salil/cs121/fall12/}. On the site, click the ``Problem Set Submission'' button and provide your login info. Once logged in, place the solutions to Parts A, B, and C in seperate files named lastname-ps#1a.pdf, lastname-ps#1b.pdf, and lastname-ps#1c.pdf respectively, in the appropriate dropboxes.\\     

    % don't mention late days at all if it's ps0
    \ifthenelse{\equal{#1}{0}} {} {
    \ifthenelse{\equal{#3}{NONE}}%
    {{\bf LATE PROBLEM SETS WILL NOT BE ACCEPTED.}}%
    {Late problem sets may be turned in until #3 at 11:59 PM with a #4\% penalty.}\\
    }
%    Please hand in Parts A, B, and C separately; each part should be stapled.\\
%    All problem sets should be dropped off in the CS 121 box in the basement of Maxwell Dworkin.\\
%    You may discuss this problem set with one other student in this class,\\
%    but please give their name and contributions with your solutions.\\
%    All written work must be prepared independently.\\
    See syllabus for collaboration policy.\\
%    WRITE YOUR TF's NAME ON EACH PART OF THE PROBLEM SET
%    WRITE YOUR TF's NAME ON THE PROBLEM SET
    } % end of \sf
%    \setlength{\parskip}{\theparskip}
   
    \end{center}
    \setcounter{Part}{1}      % initialize counters
   }      % end definition of \header
   
   \renewcommand{\PART}[1]            % ONE ARGUMENT: the part's grader
   {
    \bigskip
    \medskip
    \begin{center}
    {\bf PART \Alph{Part} (Graded by #1)}
    \end{center}
    \stepcounter{Part}
    \vspace{-0.2in}    % less PART/problem space then problem/problem
   }
   
   \renewcommand{\problem}[1]         % ONE ARGUMENT: point value of problem
   {
    \stepcounter{Problem}      % gets set to 0 because of Problem's WITHIN
    \begin{center}
    \vspace{15pt}
    PROBLEM \arabic{Problem}
     % if points is blank don't show points
    \ifthenelse{\equal{#1}{}}{}
    {\mbox{(#1 point\ifthenelse{\equal{#1}{1}}{}{s})}}
    \end{center}
   }
   
   \newcommand{\subproblem}         % NO ARGUMENTS
   {
    \p
    \stepcounter{Subproblem}
    {\sf (\ifthenelse{\value{Subproblem}<27}{\Alph{Subproblem}}%
    {\setcounter{SubproblemX}{\value{Subproblem}}%
    \addtocounter{SubproblemX}{-26}\Alph{SubproblemX}%
        \Alph{SubproblemX}})}
   }

   \newcommand{\subsolution}         % NO ARGUMENTS
   {
    \p
    \stepcounter{Subsolution}
    {\sf (\ifthenelse{\value{Subsolution}<27}{\Alph{Subsolution}}%
    {\setcounter{SubsolutionX}{\value{Subsolution}}%
    \addtocounter{SubsolutionX}{-26}\Alph{SubsolutionX}%
        \Alph{SubsolutionX}})}
   }
}

\DeclareOption{solution}{
   %% Set up for ps
   \renewcommand{\header}[4]         % 4 ARGUMENTS: ps #, due date, late
   {                     % date, late percent off
    \setlength{\parskip}{0.0in}      % Use late date NONE for no lateness.
    \begin{center}
   %{\large \bf Harvard University}\\
   {\Large \bf Computer Science 124: Programming Assignment #1}\\
   \vspace{4 mm}
   {\bf Renzo Lucioni (HUID: 90760092) and Vipul Shekhawat (HUID: 60798931)}\\
   
    %\medskip
    %{\large \bf Programming Assignment #1 Writeup}\\
   
    %\medskip
    %{\sf Due: #2\\
     %\printStudentName
     %\printCollaboration
    %} % end of \sf
%    \setlength{\parskip}{\theparskip}
   
    \end{center}
    \setcounter{Part}{1}      % initialize counters
   }      % end definition of \header
   
   \renewcommand{\PART}[1]            % ONE ARGUMENT: the part's grader
   {
    \bigskip
    \medskip
    \begin{center}
    {\bf PART \Alph{Part} (Graded by #1)}
    \end{center}
    \stepcounter{Part}
    \vspace{-0.2in}    % less PART/problem space then problem/problem
   }
   
   \renewcommand{\problem}[1]         % ONE ARGUMENT: point value of problem
   {
    \stepcounter{Problem}      % gets set to 0 because of Problem's WITHIN
    \begin{center}
    \vspace{15pt}
    PROBLEM \arabic{Problem}
     % if points is blank don't show points
    \ifthenelse{\equal{#1}{}}{}
    {\mbox{(#1 point\ifthenelse{\equal{#1}{1}}{}{s})}}
    \end{center}
   }
   
   \newcommand{\subproblem}         % NO ARGUMENTS
   {
    \p
    \stepcounter{Subproblem}
    {\sf (\ifthenelse{\value{Subproblem}<27}{\Alph{Subproblem}}%
    {\setcounter{SubproblemX}{\value{Subproblem}}%
    \addtocounter{SubproblemX}{-26}\Alph{SubproblemX}%
        \Alph{SubproblemX}})}
   }

   \newcommand{\subsolution}         % NO ARGUMENTS
   {
    \p
    \stepcounter{Subsolution}
    {\sf (\ifthenelse{\value{Subsolution}<27}{\Alph{Subsolution}}%
    {\setcounter{SubsolutionX}{\value{Subsolution}}%
    \addtocounter{SubsolutionX}{-26}\Alph{SubsolutionX}%
        \Alph{SubsolutionX}})}
   }
}

%%% Set up "solution" options
%\DeclareOption{solution}{
%   %% Set up for solution set
%   \renewcommand{\PART}[1]            % ONE ARGUMENT: the part's grader
%   {
%    \bigskip
%    \medskip
%    \begin{center}
%    {\bf PART \Alph{Part} (Graded by #1)}
%    \end{center}
%    \stepcounter{Part}
%    \vspace{-0.2in}    % less PART/problem space then problem/problem
%   }
%   \renewcommand{\header}[2][{}]    % optional argument = part
%   {                                % required argument = ps#
%     % \setlength{\parskip}{0.0in}
%     \begin{center}
%     {\large \bf Harvard University}\\
%     {\bf Computer Science 121}\\
%   
%     \medskip
%     {\bf SOLUTIONS -- Problem Set #2\ifthenelse{\equal{}{#1}}{}{, Part #1}}\\
%   
%%     \setlength{\parskip}{\theparskip}
%   
%     \end{center}
%     \setcounter{Problem}{1}
%    }      % end definition of header
%
%    \renewcommand{\problem}[1]         % ONE ARGUMENT: point value of problem
%    {
%     \bigskip               
%     \begin{center}
%     PROBLEM \arabic{Problem}
%     \ifthenelse{\equal{#1}{}}{}
%     {\mbox{(#1 point\ifthenelse{\equal{#1}{1}}{}{s})}}
%     \end{center}
%     \begin{quote}          
%     \begin{sf}
%     \begin{small}
%     \stepcounter{Problem}  
%   }
%
%   \newcommand{\subproblem}
%   {
%    \p
%    \stepcounter{Subproblem}
%    {\sf (\Alph{Subproblem})} 
%   }
%   
%   \renewcommand{\solution}
%   {
%    \end{small}
%    \end{sf}
%    \end{quote}
%    \bigskip
%    \setcounter{Subproblem}{0}
%   }
%
%   \newcommand{\subsolution}         % NO ARGUMENTS
%   {
%    \p
%    \stepcounter{Subsolution}
%    {\sf (\ifthenelse{\value{Subsolution}<27}{\Alph{Subsolution}}%
%    {\setcounter{SubsolutionX}{\value{Subsolution}}%
%    \addtocounter{SubsolutionX}{-26}\Alph{SubsolutionX}%
%        \Alph{SubsolutionX}})}
%   }
%}

%%% Pass remaining options (and 11pt) to the article class
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions*

%%% Load the article class, and select the amssymb, and
%%% latexsym packages.
\LoadClass[11pt]{article}
\RequirePackage{amssymb}
\RequirePackage{epsfig}
\RequirePackage{latexsym}
\RequirePackage{ifthen}
\RequirePackage{amsmath}
\RequirePackage{url}

%%% LaTeX macros
\newcommand{\textref}[1]{{\sf [#1] }}
\newcommand{\LP}{L\&P }
\newcommand{\lpref}[1]{\textref{\LP #1}}
% \newcommand{\huref}[1]{\textref{Hopcroft \& Ullman #1}}
\newcommand{\tab}{\hspace*{0.5in}}      % * forces spaces
\newcommand{\p}{{\ \setlength{\parskip}{0.0in} \\}}
 
%\renewcommand{\#}{{\ensuremath{{\sqcup}}}}

%%% Quarter inch indentation, empty page style.
\setlength{\parindent}{0.25in}
\pagestyle{empty}

\newcommand{\turnover}
{\medskip
 \begin{center}
 (TURN OVER!)
 \end{center}
 \pagebreak
}

%%% Various macros.
\newcommand{\Nat}{\mathbb{N}}
\newcommand{\set}[1]{\{#1\}}
\newcommand{\PTIME}{\mathrm {P}}
\newcommand*{\NP}{\ensuremath{\mathrm {NP}}}
\def\slides{0}
\def\figscale{1.0}
%\def\epsline#1{\centerline{\mbox{\epsfig{file=#1}}}}
\def\epsline#1{\centerline{\mbox{\epsfig{file=#1,scale=\figscale}}}}
%\def\eps#1{\mbox{\epsfig{file=#1}}}
\def\eps#1{\mbox{\epsfig{file=#1,scale=\figscale}}}
\def\q#1{\ensuremath{\textrm{``}#1\textrm{''}}}
\def\quine#1{\ensuremath{#1\q{#1}}}
\def\|{\mathrel|}
\def\Shuffle{\mathrm{Shuffle}}
\def\Binary{\mathrm{Binary}}
\def\L{L}
\def\Cut{\mathrm{Cut}}
\def\Min{\mathrm{Min}}
\def\Max{\mathrm{Max}}
\def\Prefix{\mathrm{Prefix}}
\def\Suffix{\mathrm{Suffix}}
\def\b#1{\overline{#1}}
\def\mathsc{\textsc}
\newcommand{\vareps}{\varepsilon}
\newcommand{\zo}{\{0,1\}}
\newcommand{\blank}{\sqcup}
\newcommand{\qaccept}{q_{\mathrm{accept}}}
\newcommand{\qreject}{q_{\mathrm{reject}}}
\newcommand{\ADFA}{A_{\mathsf{DFA}}}
\newcommand{\ATM}{A_{\mathsf{TM}}}
\newcommand{\HTM}{\mathit{HALT}_{\mathsf{TM}}}
\newcommand{\TIME}{\mathrm{TIME}}
\newcommand{\NTIME}{\mathrm{NTIME}}
\newcommand{\textprob}[1]{\textsc{#1}}
\newcommand{\mathprob}[1]{\mbox{\textmd{\textsc{#1}}}}
\newcommand{\SATsearch}{\textprob{SAT-search}}
\newcommand{\Factoring}{\textprob{Factoring}}
\newcommand{\SAT}{\mathprob{SAT}}
\newcommand{\Satisfiability}{\textprob{Satisfiability}}
\newcommand{\TravellingSalesman}{\textprob{Travelling Salesman Problem}}
\newcommand{\HamiltonianCircuit}{\textprob{Hamiltonian Circuit}}
\newcommand{\Composites}{\textprob{Composites}}
\newcommand{\MapColoring}{\textprob{Map 3-Coloring}}
\newcommand{\TSAT}{\mathprob{3-SAT}}
\newcommand{\ILP}{\mathprob{ILP}}


%\renewcommand{\or}{\vee}
%\renewcommand{\and}{\wedge}
\newcommand{\ol}[1]{\overline{#1}}
\newcommand{\Leps}{L_{\vareps}}
\newcommand{\leqm}{\leq_m}
\newcommand{\leqP}{\leq_{\mathrm{P}}}


%%% Page margins
\topmargin 0pt
\advance \topmargin by -\headheight
\advance \topmargin by -\headsep
     
\textheight 8.9in
     
\oddsidemargin 0pt
\evensidemargin \oddsidemargin
\marginparwidth 0.5in
     
\textwidth 6.5in
     
% Sans-serif comments...
\newenvironment{comment}{\setlength\parindent{0.25in}\sf}{\vspace{1pc}}

\def\smiley{\mbox{\epsfig{file=smiley.eps,height=.8pc}}}
