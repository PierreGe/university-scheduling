#ifndef __SchedSpec__
#define __SchedSpec__

#include <cstdio>
#include <vector>
#include <utility>
#include <exception>


class SchedSpec {
public:
    int T, S, E, P, X, k;
    std::vector<std::vector<int>*>* a;
    std::vector<std::vector<int>*>* b;
    std::vector<int>* c;
    std::vector<int>* d;
    std::vector<std::pair<int,int>> I;

    SchedSpec(std::vector<std::vector<int>*>* data) {
        k = 1;
        std::vector<std::vector<int>*>::iterator it = data->begin();
        // before we read T and S we make sure there are at least 2 elements in
        // the list
        if (data->size() < 2)
            throw("No values for T and S found.");
        // reading T
        if ((*it)->size() > 1)
            throw("T should be a single number.");
        this->T = (*it)->front();
        delete (*it);
        it++;
        // reading S
        if ((*it)->size() > 1)
            throw("S should be a single number.");
        this->S = (*it)->front();
        delete (*it);
        it++;
        // reading c
        if (data->size() - 2 < this->S)
            throw("Capacities and room count don't match.");
        this->c = new std::vector<int>();
        for (int i = 0; i < this->S; i++) {
            if ((*it)->size() > 1)
                throw("Each capacity should be a single number.");
            this->c->push_back((*it)->front());
            delete (*it);
            it++;
        }
        // before we read E,P,X we make sure there are at least 3 elements in
        // the list
        if (data->size() - (2 + this->c->size()) < 3)
            throw("No values for E, P and X found.");
        // reading E
        if ((*it)->size() > 1)
            throw("E should be a single number.");
        this->E = (*it)->front();
        delete (*it);
        it++;
        // reading P
        if ((*it)->size() > 1)
            throw("P should be a single number.");
        this->P = (*it)->front();
        delete (*it);
        it++;
        // reading X
        if ((*it)->size() > 1)
            throw("P should be a single number.");
        this->X = (*it)->front();
        delete (*it);
        it++;
        // reading a
        if (data->size() - (5 + this->c->size()) < this->E)
            throw("Student number and exams-per-student "
                    "mapping don't match.");
        this->a = new std::vector<std::vector<int>*>();
        for (int i = 0; i < this->E; i++) {
            this->a->push_back((*it));
            it++;
        }
        // reading b
        if (data->size() - (5 + this->c->size() +
                            this->a->size()) < this->P)
            throw("Professor number and exams-per-professor "
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
                throw("Exam durations and exam count don't match.");
            this->d = new std::vector<int>();
            for (int i = 0; i < this->X; i++) {
                if ((*it)->size() > 1)
                    throw("Each duration should be a single number.");
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
                    throw("Invalid exam mapped to a student.");
        for (int prof = 0; prof < this->P; prof++)
            for (std::vector<int>::iterator it = (*this->b)[prof]->begin();
                 it != (*this->b)[prof]->end();
                 ++it)
                if (*it > this->X)
                    throw("Invalid exam mapped to a professor.");
        // print information received
        printf("---------------------------------------- Result ----------------------------------------\n");
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

        I.push_back(std::pair<int,int>(1,8));
        for (int z = 21; z < T; z+=24) {
            if(z+11 < T)
                I.push_back(std::pair<int,int>(z,z+11));
            else
                I.push_back(std::pair<int,int>(z,T));
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

#endif