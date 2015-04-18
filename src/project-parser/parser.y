%{
#include <stdio.h>
#include <string.h>
#include <vector>

extern "C" {
    int yyparse(void);
    int yylex(void);
    int yywrap() { return 1; }
}

void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

extern int yydebug;
int main() { yydebug = 0; yyparse(); }

class SchedSpec {
    int T, S, E, P, X;
    std::vector<std::vector<int>*>* a;
    std::vector<std::vector<int>*>* b;
    std::vector<int>* c;
    std::vector<int>* d;

    public:
    SchedSpec(std::vector<std::vector<int>*>* data) {
        std::vector<std::vector<int>*>::iterator it = data->begin();
        // before we read T and S we make sure there are at least 2 elements in
        // the list
        if (data->size() < 2)
            yyerror("No values for T and S found.");
        // reading T
        if ((*it)->size() > 1)
            yyerror("T should be a single number.");
        this->T = (*it)->front();
        delete (*it);
        it++;
        // reading S
        if ((*it)->size() > 1)
            yyerror("S should be a single number.");
        this->S = (*it)->front();
        delete (*it);
        it++;
        // reading c
        if (data->size() - 2 < this->S)
            yyerror("Capacities and room count don't match.");
        this->c = new std::vector<int>();
        for (int i = 0; i < this->S; i++) {
            if ((*it)->size() > 1)
                yyerror("Each capacity should be a single number.");
            this->c->push_back((*it)->front());
            delete (*it);
            it++;
        }
        // before we read E,P,X we make sure there are at least 3 elements in
        // the list
        if (data->size() - (2 + this->c->size()) < 3)
            yyerror("No values for E, P and X found.");
        // reading E
        if ((*it)->size() > 1)
            yyerror("E should be a single number.");
        this->E = (*it)->front();
        delete (*it);
        it++;
        // reading P
        if ((*it)->size() > 1)
            yyerror("P should be a single number.");
        this->P = (*it)->front();
        delete (*it);
        it++;
        // reading X
        if ((*it)->size() > 1)
            yyerror("P should be a single number.");
        this->X = (*it)->front();
        delete (*it);
        it++;
        // reading a
        if (data->size() - (5 + this->c->size()) < this->E)
            yyerror("Student number and exams-per-student "
                    "mapping don't match.");
        this->a = new std::vector<std::vector<int>*>();
        for (int i = 0; i < this->E; i++) {
            this->a->push_back((*it));
            it++;
        }
        // reading b
        if (data->size() - (5 + this->c->size() +
                            this->a->size()) < this->P)
            yyerror("Professor number and exams-per-professor "
                    "mapping don't match.");
        this->b = new std::vector<std::vector<int>*>();
        for (int i = 0; i < this->P; i++) {
            this->b->push_back((*it));
            it++;
        }
        // reading d
        if (data->size() - (5 + this->c->size() +
                            this->a->size() +
                            this->b->size()) > 0) {
            if (data->size() - (5 + this->c->size() +
                                this->a->size() +
                                this->b->size()) < this->X)
                yyerror("Exam durations and exam count don't match.");
            this->d = new std::vector<int>();
            for (int i = 0; i < this->X; i++) {
                if ((*it)->size() > 1)
                    yyerror("Each duration should be a single number.");
                this->d->push_back((*it)->front());
                delete (*it);
                it++;
            }
        } else {
            this->d = NULL;
        }
        // final check, every index in a b should be valid
        for (int student = 0; student < this->E; student++)
            for (std::vector<int>::iterator it = (*this->a)[student]->begin();
                 it != (*this->a)[student]->end();
                 ++it)
                if (*it > this->X)
                    yyerror("Invalid exam mapped to a student.");
        for (int prof = 0; prof < this->P; prof++)
            for (std::vector<int>::iterator it = (*this->b)[prof]->begin();
                 it != (*this->b)[prof]->end();
                 ++it)
                if (*it > this->X)
                    yyerror("Invalid exam mapped to a professor.");
        // print information received
        printf("T = %d\n", this->T);
        printf("|S| = %d\n", this->S);
        int i = 0;
        for (std::vector<int>::iterator it = this->c->begin();
             it != this->c->end();
             ++it) {
            printf("c(s%d) = %d\n", ++i, (*it));
        }
        printf("|E| = %d\n", this->E);
        printf("|P| = %d\n", this->P);
        printf("|X| = %d\n", this->X);
        i = 0;
        for (std::vector<std::vector<int>*>::iterator it = this->a->begin();
             it != this->a->end();
             ++it) {
            printf("a(e%d) = { ", ++i);
            for (int j = 0; j < (*it)->size(); j++)
                printf("%d ", (**it)[j]);
            printf("}\n");
        }
        i = 0;
        for (std::vector<std::vector<int>*>::iterator it = this->b->begin();
             it != this->b->end();
             ++it) {
            printf("b(p%d) = { ", ++i);
            for (int j = 0; j < (*it)->size(); j++)
                printf("%d ", (**it)[j]);
            printf("}\n");
        }
        if (this->d != NULL) {
            i = 0;
            for (std::vector<int>::iterator it = this->d->begin();
                 it != this->d->end();
                 ++it) {
                printf("d(x%d) = %d\n", ++i, (*it));
            }
        }
    }

    ~SchedSpec() {
        if (this->a != NULL)
            delete a;
        if (this->b != NULL)
            delete b;
        if (this->c != NULL)
            delete c;
        if (this->d != NULL)
            delete d;
    }
};
%}

%error-verbose
%union { int number; void* pter; }
%token SEMICOLON COMMA
%token <number> NUMBER

%type <pter> number_list value_list values
%start values
%%
values:
      value_list {
          $$ = new SchedSpec(
              static_cast<std::vector<std::vector<int>*>*>($1));
      }

value_list: /* essentially a semicolon-separated value list */
      number_list {
          $$ = new std::vector<std::vector<int>*>();
          static_cast<std::vector<std::vector<int>*>*>($$)->push_back(
              static_cast<std::vector<int>*>($1)
          );
      }
      |
      value_list SEMICOLON number_list {
          $$ = $1;
          static_cast<std::vector<std::vector<int>*>*>($$)->push_back(
              static_cast<std::vector<int>*>($3)
          );
      }
      |
      value_list SEMICOLON {
          $$ = $1;
      }

number_list: /* essentially a comma-separated value list */
      NUMBER {
          if ($1 <= 0) yyerror("Unexpected 0 value");
          $$ = new std::vector<int>();
          static_cast<std::vector<int>*>($$)->push_back($1);
      }
      |
      number_list COMMA NUMBER { 
          if ($3 <= 0) yyerror("Unexpected 0 value");
          $$ = $1;
          static_cast<std::vector<int>*>($$)->push_back($3);
      }
      |
      number_list COMMA { $$ = $1; }
%%
