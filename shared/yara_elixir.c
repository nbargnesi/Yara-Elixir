#include <stdio.h>
#include <yara.h>
#include <erl_nif.h>

// Wraps the Yara initializer
extern int init_yara();

// Wraps the Yara finalizer
extern int destroy_yara();

// Call this function when you start using Yara.
static ERL_NIF_TERM init_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    int ret;
    ret = yr_initialize();
#ifdef CHATTY
    fprintf(stdout, "yr_initialize: %d\n", ret);
#endif
    return enif_make_int(env, ret);
}

// Call this function when you are finished using Yara.
static ERL_NIF_TERM destroy_yara_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    int ret;
    ret = yr_finalize();
#ifdef CHATTY
    fprintf(stdout, "yr_finalize: %d\n", ret);
#endif
    return enif_make_int(env, ret);
}

static ErlNifFunc nif_funcs[] = {
    {"init_yara", 0, init_yara_nif},
    {"destroy_yara", 0, destroy_yara_nif}
};

// ERL_NIF_INIT args
//     yara_elixir - C identifier converted to a string
//     nif_funcs - name, arity, and function pointer of each NIF
ERL_NIF_INIT(Elixir.YaraElixir, nif_funcs, NULL, NULL, NULL, NULL)
