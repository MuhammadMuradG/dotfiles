# .zshenv is always sourced.
# Most ${ENV_VAR} variables should be saved here.
# It is loaded before .zshrc
# -----------------------------------------------------------------------------

# Activate venv if exist
if [[ -n $VIRTUAL_ENV && -e "${VIRTUAL_ENV}/bin/activate" ]]; then
	source "${VIRTUAL_ENV}/bin/activate"
fi
