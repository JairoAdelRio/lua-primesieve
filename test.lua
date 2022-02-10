local p=require"primesieve"
local concat = table.concat
local n1 = 200
local n2 = 3000
local n3 = 45
local n4 = 123
local n5 = 417
local n6 = 2022
print("Primes from ".. n1 .. " to " .. n2 ..":")
print(concat(p.generate_primes(200,3000),", "))

print(n3 .. " primes from " .. n4 .. ":")
print(concat(p.generate_n_primes(200,3000),", "))

print(n5 .. "-th prime:")
print(p.nth_prime(n5))

print("How many primes less or equal than " .. n6 .. " are there?")
print(p.count_primes(n6))

print("How many prime twins less or equal than " .. n6 .. " are there?")
print(p.count_twins(n6))

print("How many prime triplets less or equal than " .. n6 .. " are there?")
print(p.count_triplets(n6))

print("How many prime quadruplets less or equal than " .. n6 .. " are there?")
print(p.count_quadruplets(n6))

print("How many prime quintuplets less or equal than " .. n6 .. " are there?")
print(p.count_quintuplets(n6))

print("How many prime sextuplets less or equal than " .. n6 .. " are there?")
print(p.count_sextuplets(n6))

print(p.version)