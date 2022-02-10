#include"lua.h"
#include"lauxlib.h"

#include"primesieve.h"

#define MYNAME "primesieve"
#define MYVERSION \
  MYNAME " library for " LUA_VERSION " / Feb 2022 / " \
  "using primesieve " PRIMESIEVE_VERSION

#define MYTYPE MYNAME " iterator"

#define M_COUNT_TUPLE(TUPLE)                               \
int F_count_##TUPLE(lua_State *L)                          \
{                                                          \
  lua_Integer start, stop;                                 \
  lua_settop(L,2);                                         \
  if (lua_isnil(L,2))                                      \
    {                                                      \
      start = 0;                                           \
      stop  = luaL_checkinteger(L,1);                      \
    }                                                      \
  else                                                     \
    {                                                      \
      start = luaL_checkinteger(L,1);                      \
      stop  = luaL_checkinteger(L,2);                      \
    }                                                      \
  lua_pushinteger(L,primesieve_count_##TUPLE(start,stop)); \
  return 1;                                                \
}

static primesieve_iterator* A_new_iterator(lua_State *L)
{
  primesieve_iterator *x;
  x = (primesieve_iterator *)lua_newuserdata(L, sizeof(primesieve_iterator));
  luaL_setmetatable(L,MYTYPE);
  return x;
}

static int F_iterator(lua_State *L)
{
  primesieve_iterator *x;
  x = A_new_iterator(L);
  primesieve_init(x);
  return 1;
}

static int F_next_prime(lua_State *L)
{
  lua_Integer n;
  primesieve_iterator *x;
  x = (primesieve_iterator *)luaL_checkudata(L,1,MYTYPE);
  n = primesieve_next_prime(x);
  lua_pushinteger(L,n);
  return 1;
}

static int F_prev_prime(lua_State *L)
{
  lua_Integer n;
  primesieve_iterator *x;
  x = (primesieve_iterator *)luaL_checkudata(L,1,MYTYPE);
  n = primesieve_prev_prime(x);
  lua_pushinteger(L,n);
  return 1;
}

static int F_skipto(lua_State *L)
{
  lua_Integer start, stop;
  primesieve_iterator *x;
  x = (primesieve_iterator *)luaL_checkudata(L,1,MYTYPE);
  start = luaL_checkinteger(L,2);
  stop  = luaL_checkinteger(L,3);
  primesieve_skipto(x,start,stop);
  return 0;
}

static int F_iterator_gc(lua_State *L)
{
  primesieve_iterator *x;
  x = (primesieve_iterator *)luaL_checkudata(L,1,MYTYPE);
  primesieve_free_iterator(x);
  return 0;
}

static int F_generate_primes(lua_State *L)
{
  lua_Integer start, stop;
  size_t size;
  lua_settop(L,2);
  if (lua_isnil(L,2))
    {
      start = 0;
      stop  = luaL_checkinteger(L,1);
    }
  else
    {
      start = luaL_checkinteger(L,1);
      stop  = luaL_checkinteger(L,2);
    }
  long long* primes = (long long*) primesieve_generate_primes(start, stop, &size, LONGLONG_PRIMES);
  lua_createtable(L,size,0);
  for (size_t i = 0; i < size; i++)
  {
    lua_pushinteger(L,primes[i]);
    lua_seti(L,-2,i+1);
  }
  primesieve_free(primes);
  return 1;
}

static int F_generate_primes_hash(lua_State *L)
{
  lua_Integer start, stop;
  size_t size;
  lua_settop(L,2);
  if (lua_isnil(L,2))
    {
      start = 0;
      stop  = luaL_checkinteger(L,1);
    }
  else
    {
      start = luaL_checkinteger(L,1);
      stop  = luaL_checkinteger(L,2);
    }
  long long* primes = (long long*) primesieve_generate_primes(start, stop, &size, LONGLONG_PRIMES);
  lua_createtable(L,size,0);
  for (size_t i = 0; i < size; i++)
  {
    lua_pushboolean(L,1);
    lua_seti(L,-2,primes[i]);
  }
  primesieve_free(primes);
  return 1;
}

static int F_generate_n_primes(lua_State *L)
{
  lua_Integer start, n;
  lua_settop(L,2);
  start = luaL_optinteger(L,2,0);
  n     = luaL_checkinteger(L,1);
  long long* primes = (long long*) primesieve_generate_n_primes(n, start, LONGLONG_PRIMES);
  lua_createtable(L,n,0);
  for (lua_Integer i = 0; i < n; i++)
  {
    lua_pushinteger(L,primes[i]);
    lua_seti(L,-2,i+1);
  }
  primesieve_free(primes);
  return 1;
}

static int F_generate_n_primes_hash(lua_State *L)
{
  lua_Integer start, n;
  lua_settop(L,2);
  start = luaL_optinteger(L,2,0);
  n     = luaL_checkinteger(L,1);
  long long* primes = (long long*) primesieve_generate_n_primes(n, start, LONGLONG_PRIMES);
  lua_createtable(L,n,0);
  for (lua_Integer i = 0; i < n; i++)
  {
    lua_pushboolean(L,1);
    lua_seti(L,-2,primes[i]);
  }
  primesieve_free(primes);
  return 1;
}

static int F_nth_prime(lua_State *L)
{
  lua_Integer n, start;
  lua_settop(L,2);
  n     = luaL_checkinteger(L,1);
  start = luaL_optinteger(L,2,0);
  lua_pushinteger(L,primesieve_nth_prime(n,start));
  return 1;
}

M_COUNT_TUPLE(primes);

M_COUNT_TUPLE(twins);

M_COUNT_TUPLE(triplets);

M_COUNT_TUPLE(quadruplets);

M_COUNT_TUPLE(quintuplets);

M_COUNT_TUPLE(sextuplets);

static const struct luaL_Reg L_primesieve [] =
{
  {"generate_primes", F_generate_primes},
  {"generate_primes_hash", F_generate_primes_hash},
  {"generate_n_primes", F_generate_n_primes},
  {"generate_n_primes_hash", F_generate_n_primes_hash},
  {"nth_prime", F_nth_prime},
  {"count_primes", F_count_primes},
  {"count_twins", F_count_twins},
  {"count_triplets", F_count_triplets},
  {"count_quadruplets", F_count_quadruplets},
  {"count_quintuplets", F_count_quintuplets},
  {"count_sextuplets", F_count_sextuplets},
  {"iterator", F_iterator},
  {"next_prime", F_next_prime},
  {"prev_prime", F_prev_prime},
  {"skipto", F_skipto},
  {"__gc", F_iterator_gc},
  {NULL, NULL}
};

LUALIB_API int luaopen_primesieve(lua_State *L)
{
 luaL_newmetatable(L,MYTYPE);
 luaL_setfuncs(L,L_primesieve,0);
 lua_pushliteral(L,"version");
 lua_pushliteral(L,MYVERSION);
 lua_settable(L,-3);
 lua_pushliteral(L,"__index");
 lua_pushvalue(L,-2);
 lua_settable(L,-3);
 return 1;
}