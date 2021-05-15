# .zshenv is always sourced.
# Most ${ENV_VAR} variables should be saved here.
# It is loaded before .zshrc
# -----------------------------------------------------------------------------

# Activate venv if exist
# -n <string>: true if length of string is non-zero.
# -e <file>: true if file exists.
# REF: http://zsh.sourceforge.net/Doc/Release/Conditional-Expressions.html#Conditional-Expressions
if [[ -n $VIRTUAL_ENV && -e "${VIRTUAL_ENV}/bin/activate" ]]; then
	source "${VIRTUAL_ENV}/bin/activate"
fi
