#include <iostream>
using namespace std;
#include "evalobj.h"


/**
 * Add a variable to a given environment.
 * name: The name of the variable to assign.
 * namec: The length of the variable name.
 * value: The value to assign to this name.
 * env: A pointer to the environment to which to add this variable.
 */
struct env *
envAdd(string name, int value, struct env *env) {
    struct env *result = new struct env();
    result->var = name;
    result->value = value;
    result->next = env;
    return result;
}


/**
 * Retrieve the value of a variable in an environment.
 * name: The name of the variable to retrieve.
 * env: The environment to search.
 */
int envGet(string name, struct env *env) {
    struct env *var = env;
    while (var) {
        if (name == var->var) {
            return var->value;
        }
        var = var->next;
    }
    cerr << "Couldn't find variable in environment." << endl;
    return -1;
}


/**
 * Remove the last-added variable from an environment.
 */
struct env *envPop(struct env *env) {
    struct env *result = env->next;
    delete env;
    return result;
}


int OpApp::eval(env* environ) {
    int total = -1;
    auto arguments = args;
    switch(op) {
        case plusop:
        {
            total = 0;
            while (arguments) {
                total += arguments->head->eval(environ);
                arguments = arguments->tail;
            }
            break;
        }
        case timesop:
        {
            total = 1;
            while (arguments) {
                total *= arguments->head->eval(environ);
                arguments = arguments->tail;
            }
            break;
        }
        default: {
            cerr << "Invalid operator!" << endl;
            break;
        }
    }
    return total;
}


int Constant::eval(env* environ) {
    return n;
}


int Var::eval(env *environ) {
    return envGet(name, environ);
}


int Let::eval(env *environ) {
    environ = envAdd(bvar, bexp->eval(environ), environ);
    auto result = body->eval(environ);
    envPop(environ);
    return result;
}
