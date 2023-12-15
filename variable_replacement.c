#include "main.h"

/* check_env - Scans environment variables for matches */
void check_env(r_var **h, char *in, data_shell *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;
    for (row = 0; _envr[row]; row++) {
        for (j = 1, chr = 0; _envr[row][chr]; chr++) {
            if (_envr[row][chr] == '=') {
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }
            if (in[j] == _envr[row][chr]) j++;
            else break;
        }
    }
    for (j = 0; in[j]; j++) {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }
    add_rvar_node(h, j, NULL, 0);
}

/* check_vars - Checks if input contains special variables */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
    int i, lst, lpd;

    lst = _strlen(st);
    lpd = _strlen(data->pid);

    for (i = 0; in[i]; i++) {
        if (in[i] == '$') {
            // Special variable processing
            if (in[i + 1] == '?')
                add_rvar_node(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                add_rvar_node(h, 2, data->pid, lpd), i++;
            else
                check_env(h, in + i, data);
        }
    }
    return (i);
}

/* replaced_input - Replaces strings with variables */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
    r_var *indx;
    int i, j, k;

    indx = *head;
    for (j = i = 0; i < nlen; i++) {
        if (input[j] == '$') {
            // Variable replacement logic
            new_input[i] = (indx->len_var && !indx->len_val) ? '\0' : input[j];
            j += (indx->len_var && !indx->len_val) ? indx->len_var : 1;
            if (indx->len_var && indx->len_val) {
                for (k = 0; k < indx->len_val; k++, i++)
                    new_input[i] = indx->val[k];
                j += indx->len_var;
                i--;
            }
            indx = indx->next;
        } else {
            new_input[i] = input[j++];
        }
    }
    return (new_input);
}

/* rep_var - Replaces variables in the input string */
char *rep_var(char *input, data_shell *datash)
{
    r_var *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    status = aux_itoa(datash->status);
    head = NULL;

    olen = check_vars(&head, input, status, datash);

    if (!head) {
        free(status);
        return input;
    }

    indx = head;
    nlen = olen;

    while (indx) {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    new_input = replaced_input(&head, input, new_input, nlen);

    free(input);
    free(status);
    free_rvar_list(&head);

    return new_input;
}
