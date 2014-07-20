#include <stdio.h>
#include "syntax.c"

void write_skeleton(Syntax *syntax) {
    FILE *out = fopen("out.s", "wb");

    fprintf(out, ".text\n");
    // We seem to require at least 8 spaces for indentation.
    fprintf(out, "    .global _start\n\n");
    fprintf(out, "_start:\n");

    // TODO: do everything in eax, then move to ebx for exit.
    // TODO: recurse
    if (syntax->type == UNARY_OPERATOR) {
        UnarySyntax *unary_syntax = syntax->expression;

        fprintf(out, "    movl    $%d, %%ebx\n", unary_syntax->expression->value);

        if (unary_syntax->unary_type == BITWISE_NEGATION) {
            fprintf(out, "    not     %%ebx\n");
        } else {
            fprintf(out, "    test    $0xFFFFFFFF, %%ebx\n");
            fprintf(out, "    setz    %%bl\n");
        }
    } else {
        // Exit code as specified.
        fprintf(out, "    movl    $%d, %%ebx\n", syntax->value);
    }

    fprintf(out, "    movl    $1, %%eax\n");
    fprintf(out, "    int     $0x80\n");
    
    fclose(out);
}

void write_assembly(Syntax *syntax) {
    write_skeleton(syntax);
}
