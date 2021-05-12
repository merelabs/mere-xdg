#include "environment.h"


const char* Mere::XDG::Env::Name::SESSION_DESKTOP = "XDG_SESSION_DESKTOP";
const char* Mere::XDG::Env::Name::CURRENT_DESKTOP = "XDG_CURRENT_DESKTOP";

const char* Mere::XDG::Env::Name::DATA_HOME   = "XDG_DATA_HOME";
const char* Mere::XDG::Env::Name::CONFIG_HOME = "XDG_CONFIG_HOME";
const char* Mere::XDG::Env::Name::CACHE_HOME  = "XDG_CACHE_HOME";
const char* Mere::XDG::Env::Name::ICON_HOME   = "XDG_ICON_HOME";

const char* Mere::XDG::Env::Name::DATA_DIRS   = "XDG_DATA_DIRS";
const char* Mere::XDG::Env::Name::CONFIG_DIRS = "XDG_CONFIG_DIRS";

const char* Mere::XDG::Env::Name::RUNTIME_DIR = "XDG_RUNTIME_DIR";


const char* Mere::XDG::Env::Value::SESSION_DESKTOP = "MERE";
const char* Mere::XDG::Env::Value::CURRENT_DESKTOP = "MERE";

const char* Mere::XDG::Env::Value::DATA_HOME   = "$HOME/.local/share/";
const char* Mere::XDG::Env::Value::CONFIG_HOME = "$HOME/.config/";
const char* Mere::XDG::Env::Value::CACHE_HOME  = "$HOME/.cache/";
const char* Mere::XDG::Env::Value::ICON_HOME   = "$HOME/.icons/";

const char* Mere::XDG::Env::Value::DATA_DIRS   = "/usr/local/share/:/usr/share/";

// we made a bit change here; added /usr/local/etc/xdg
const char* Mere::XDG::Env::Value::CONFIG_DIRS = "/usr/local/etc/xdg/:/etc/xdg/";

// where did we find this one, in which spec?
const char* Mere::XDG::Env::Value::RUNTIME_DIR = "/tmp/mere-$USER/";


