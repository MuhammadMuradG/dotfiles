# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
setopt beep
bindkey -v
# End of lines configured by zsh-newuser-install


# The func compinstall can be # run by a user to set up the completion
# system for use, which also provides options for more advanced usage.
# The following lines were added by compinstall.
zstyle :compinstall filename '/home/MuhammadMuradFbsd/.zshrc'
zstyle ':omz:alpha:lib:git' async-prompt no

autoload -Uz compinit
compinit
# End of lines added by compinstall


# -----------------------------------------------------------------------------
# Info
# -----------------------------------------------------------------------------
# There are five startup files that zsh will read commands from:
# $ZDOTDIR/.zshenv
# $ZDOTDIR/.zprofile
# $ZDOTDIR/.zshrc
# $ZDOTDIR/.zlogin
# $ZDOTDIR/.zlogout

# If ZDOTDIR is not set, then the value of HOME is used; this is the usual case.

# `.zshenv' is sourced on all invocations of the shell, unless the -f option is
# set. It should contain commands to set the command search path, plus other
# important environment variables. `.zshenv' should not contain commands that
# produce output or assume the shell is attached to a tty.

# `.zshrc' is sourced in interactive shells. It should contain commands to set
# up aliases, functions, options, key bindings, etc.

# `.zlogin' is sourced in login shells. It should contain commands that should
# be executed only in login shells. `.zlogout' is sourced when login shells exit.
# `.zprofile' is similar to `.zlogin', except that it is sourced before `.zshrc'.
# `.zprofile' is meant as an alternative to `.zlogin' for ksh fans; the two are
# not intended to be used together, although this could certainly be done if
# desired. `.zlogin' is not the place for alias definitions, options, environment
# variable settings, etc.; as a general rule, it should not change the shell
# environment at all. Rather, it should be used to set the terminal type and
# run a series of external commands (fortune, msgs, etc).


# -----------------------------------------------------------------------------
# Customs Configuration
# -----------------------------------------------------------------------------
# Set environment variables
export LANG=en_US.UTF-8   # system locale
export EDITOR=nvim        # editor
export PAGER=less      # zathura or less

# Set additional options
setopt INC_APPEND_HISTORY   # Commands are added to the history immediately
setopt HIST_IGNORE_ALL_DUPS # Don't writing duplicated commands to the history
setopt HIST_IGNORE_SPACE    # Don't writing leading space commands to the history
setopt prompt_subst         # Reevaluate the prompt each displaying time

# Bind keys
bindkey "^[[3~" delete-char
bindkey "^[[H"  beginning-of-line
bindkey '^[[7~' beginning-of-line
bindkey "^[[F" end-of-line
bindkey '^[[8~' end-of-line
bindkey '\e[A' history-beginning-search-backward
bindkey '\e[B' history-beginning-search-forward

# Exclude failed commands from history file; This function is executed before
# the command line is written to history. If it does return 1, the current
# command line is neither appended to the history file nor to the
# local history stack.
zshaddhistory() { whence ${${(z)1}[1]} >| /dev/null || return 1 }

# For colorized ls output
export CLICOLOR=1

# Enable keyboard navigation of completions in menu
# (not just tab/shift-tab but cursor keys as well):
zstyle ':completion:*' menu select

# Allow completion of ..<Tab> to ../ and beyond.
zstyle -e ':completion:*' special-dirs '[[ $PREFIX = (../)#(..) ]] && reply=(..)'

# Categorize completion suggestions with headings
zstyle ':completion:*' group-name ''
# Style the group names
zstyle ':completion:*' format %F{blue}%B%U%{$__DOTS[ITALIC_ON]%}%d%{$__DOTS[ITALIC_OFF]%}%b%u%f

# Colored completion (different colors for dirs/files/etc)
zstyle ':completion:*' list-colors "${(s.:.)LS_COLORS}"

# Colored command options
zstyle ':completion:*:options' list-colors '=^(-- *)=34'

# Colored process from kill output
zstyle ':completion:*:*:kill:*' list-colors '=(#b) #([0-9]#)*( *[a-z])*=34=31=33'

# My aliases. '-g': for global, allow using anywhere in the commands.
alias -g full-update='sudo freebsd-update fetch; sudo freebsd-update install; sudo pkg update -f; sudo pkg upgrade -y; sudo pkg autoremove -y; sudo pkg clean -ay'
alias incognito=' export INCOGNITO_MODE=1; unset HISTFILE'
alias deincognito=" export INCOGNITO_MODE=''; fc -p ~/.histfile"

# Check if incognito mode is activated
if [[ ! -z ${INCOGNITO_MODE} ]]; then
	fc -p ~/.histfile
	unset HISTFILE
fi

# Load my theme
source ~/.zsh-theme


# -----------------------------------------------------------------------------
# Zplug plugins
# -----------------------------------------------------------------------------
source ~/.zplug/init.zsh

zplug "zsh-users/zsh-autosuggestions"
zplug "zpm-zsh/colorize"
zplug "plugins/git", from:oh-my-zsh

# Set the priority when loading
# e.g., zsh-syntax-highlighting must be loaded
# after executing compinit command and sourcing other plugins
# (If the defer tag is given 2 or above, run after compinit command)
zplug "zsh-users/zsh-syntax-highlighting", defer:2

# Install plugins if there are plugins that have not been installed
if ! zplug check --verbose; then
    printf "Install? [y/N]: "
    if read -q;then
        echo; zplug install
    fi
fi

# Then, source plugins and add commands to $PATH
zplug load
