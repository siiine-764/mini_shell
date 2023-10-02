#include "minishell.h"

//t_vars_g	g_global_vars;

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    struct Node* head = NULL;
    create_env(env, &head);
    // my struct
    t_cmd *my_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    
    // for example : //
    char *flag = "-nnnn";
    char *arguments[][3] = 
    {
        {"cd", "..", ""},
        {"echo", "xx", "sssss"},
    };
    if (my_cmd == NULL)
    {
        perror("Memory allocation failed");
        return 1;
    }
    my_cmd->arguments = (char ***)malloc(2 * sizeof(char **));
    if (my_cmd->arguments == NULL)
    {
        perror("Memory allocation failed");
        free(my_cmd);
        return 1;
    }
    for (int i = 0; i < 2; i++)
    {
        my_cmd->arguments[i] = (char **)malloc(3 * sizeof(char *));
        if (my_cmd->arguments[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }

        for (int j = 0; j < 3; j++) {
            my_cmd->arguments[i][j] = arguments[i][j];
        }
    }
    my_cmd->flag = flag;

    // end example //

    // //
    char *input;

    rl_initialize();
    while (1)
    {
        input = readline("minishell$ ");
        add_history(input);
        // my function
        excute_cpy(my_cmd, env, head, input);

        free(input);
    }
    // //

    return 0;
}