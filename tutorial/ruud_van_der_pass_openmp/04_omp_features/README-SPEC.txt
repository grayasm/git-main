*
    OpenMP 3.1 specifications
    An extended explanation of each directive as they are described in the pdf.


    #pragma omp parallel [clause [[,] clause] ..] new-line
            structured-block

            [clause]=
            if (scalar-expr)
            num_threads (integer-expr)
            default (shared | none)
            private (list)
            firstprivate (list)
            shared (list)
            copyin (list)
            reduction (operator: list)


    #pragma omp for [clause [[,] clause] ...] new-line
            for-loops

            [clause]=
            private (list)
            firstprivate (list)
            lastprivate (list)
            reduction (operator: list)
            schedule (kind [,chunk_size])
            collapse (n)
            ordered
            nowait


    #pragma omp sections [clause [[,] clause] ...] new-line
            {
            [#pragma omp section new-line]
                     structured-block

            [#pragma omp section new-line]
                     structured-block
            }

            [clause]=
            private (list)
            firstprivate (list)
            lastprivate (list)
            reduction (operator: list)
            nowait


    #pragma omp single [clause [[,] clause] ...] new-line
            structured-block

            [clause]=
            private (list)
            firstprivate (list)
            copyprivate (list)
            nowait


    #pragma omp task [clause [[,] clause] ...] new-line
            structured-block

            [clause]=
            if (scalar-expr)
            final (scalar-expr)
            untied
            default (shared | none)
            mergeable
            private (list)
            firstprivate (list)
            shared (list)


    #pragma omp taskyield new-line
