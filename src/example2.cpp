#include <iostream>
#include "Problem.hpp"



Problem::Problem()
{

}

Problem::Problem(Problem* modelerToCopy)
{

}

Problem::~Problem()
{

}

void Problem::RunQ1(string in_file_name, string dimacs_file, string out_file_name)
{
    Parser p;
    p.Parsing1(in_file_name);
    TABLE_BOOL initial_info = p.GetMatrix();

    int card_a = initial_info.size();
    int card_b = initial_info[0].size();
    int card_c = p.GetNbGroups();

    // Exclusion des AB
    VECT_UINT ab_variables;
    this->GenerateVariables(ab_variables, card_a*card_b);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ab;
        for(int j = 0 ; j<card_b ; j++)
        {
            sub_ab.push_back( ab_variables[(i*card_b)+j] );
            if (!initial_info[i][j])
                s.AddUnit(Lit(NOT,  ab_variables[(i*card_b)+j] ));
        }
        unsigned int k = 1; // PASSER k PARAM
        this->ALO(sub_ab);
        this->Binary(sub_ab, k);
    }


    // Exclusions des AC
    VECT_UINT ac_variables;
    VECT_UINT g_variables;
    this->GenerateVariables(ac_variables, card_a*card_c);
    this->GenerateVariables(g_variables, card_c);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ac;
        for(int j = 0 ; j<card_c ; j++)
        {
            sub_ac.push_back( ac_variables[(i*card_c)+j] );
            this->s.AddBinary(Lit(IS, g_variables[j]), Lit(NOT, ac_variables[(i*card_c)+j]));
        }
        unsigned int k = 1; // PASSER k PARAM
        this->ALO(sub_ac);
        this->Binary(sub_ac, k);
    }

    VECT_UINT abc_variables;
    this->GenerateVariables(abc_variables, card_a*card_b*card_c);

    // (abc <-> ab ^ ac)
    for (int i = 0; i < card_a; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            for (int k = 0; k < card_c; k++)
            {
                VECT_LIT temp_one;
                temp_one.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_one.push_back(Lit(IS, ab_variables[ (i*card_b)+j ]));
                VECT_LIT temp_two;
                temp_two.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_two.push_back(Lit(IS, ac_variables[ (i*card_c)+k ]));
                VECT_LIT temp_three;
                temp_three.push_back(Lit(IS, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_three.push_back(Lit(NOT, ab_variables[ (i*card_b)+j ]));
                temp_three.push_back(Lit(NOT, ac_variables[ (i*card_c)+k ]));
                this->s.AddClause(temp_one);
                this->s.AddClause(temp_two);
                this->s.AddClause(temp_three);
            }
        }
    }


    // Pour chaque groupe, pour chaque instrument joué dans le groupe, il y a alo(mussicien) et amo(musicien)
    for (int i = 0; i < card_c; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            VECT_UINT temp;
            for (int k = 0; k < card_a; k++)
            {
                temp.push_back(abc_variables[ (k*card_b*card_c) + (j*card_c) + i ]);
            }
            unsigned int k = 1; // PASSER k PARAM
            this->ALO(temp, g_variables[i]);
            this->Binary(temp, k);
        }
    }

    this->s.ToDimacs(dimacs_file);

    system(("./MiniSat_v1.14_linux "+ dimacs_file + " " + out_file_name).c_str());

    SolutionInterpreter x;
    x.Interpret(out_file_name, card_a, card_b, card_c, abc_variables);

}


void Problem::RunQ2(string in_file_name, string dimacs_file, string out_file_name)
{
    Parser p;
    p.Parsing2(in_file_name);
    TABLE_BOOL initial_info = p.GetMatrix();

    int card_a = initial_info.size();
    int card_b = initial_info[0].size();
    int card_c = p.GetNbGroups();

    VECT_UINT maximum_groups = p.GetMaxGroups();

    // Exclusion des AB
    VECT_UINT ab_variables;
    this->GenerateVariables(ab_variables, card_a*card_b);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ab;
        for(int j = 0 ; j<card_b ; j++)
        {
            sub_ab.push_back( ab_variables[(i*card_b)+j] );
            if (!initial_info[i][j])
                s.AddUnit(Lit(NOT,  ab_variables[(i*card_b)+j] ));
        }
        this->ALO(sub_ab);
    }

    std::cout << "ACCCCCCC" << std::endl;

    // Exclusions des AC
    VECT_UINT ac_variables;
    VECT_UINT g_variables;
    this->GenerateVariables(ac_variables, card_a*card_c);
    this->GenerateVariables(g_variables, card_c);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ac;
        for(int j = 0 ; j<card_c ; j++)
        {
            sub_ac.push_back( ac_variables[(i*card_c)+j] );
            this->s.AddBinary(Lit(IS, g_variables[j]), Lit(NOT, ac_variables[(i*card_c)+j]));
        }
        this->ALO(sub_ac);
        std::cout << "K: " << maximum_groups[i] << std::endl;
        this->Binary(sub_ac, maximum_groups[i]);
        //this->General(sub_ac, maximum_groups[i], BINARY);
        //this->AMK_Pairwise(sub_ac, maximum_groups[i]);
    }

    std::cout << "EQUIV" << std::endl;

    VECT_UINT abc_variables;
    this->GenerateVariables(abc_variables, card_a*card_b*card_c);

    // (abc <-> ab ^ ac)
    for (int i = 0; i < card_a; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            for (int k = 0; k < card_c; k++)
            {
                VECT_LIT temp_one;
                temp_one.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_one.push_back(Lit(IS, ab_variables[ (i*card_b)+j ]));
                VECT_LIT temp_two;
                temp_two.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_two.push_back(Lit(IS, ac_variables[ (i*card_c)+k ]));
                VECT_LIT temp_three;
                temp_three.push_back(Lit(IS, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_three.push_back(Lit(NOT, ab_variables[ (i*card_b)+j ]));
                temp_three.push_back(Lit(NOT, ac_variables[ (i*card_c)+k ]));
                this->s.AddClause(temp_one);
                this->s.AddClause(temp_two);
                this->s.AddClause(temp_three);
            }
        }
    }

    std::cout << "END EQUIV" << std::endl;

    // Pour chaque groupe, pour chaque instrument joué dans le groupe, il y a alo(mussicien) et amo(musicien)
    for (int i = 0; i < card_c; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            VECT_UINT temp;
            for (int k = 0; k < card_a; k++)
            {
                temp.push_back(abc_variables[ (k*card_b*card_c) + (j*card_c) + i ]);
            }
            unsigned int k = 1;
            this->ALO(temp, g_variables[i]);
            this->Binary(temp, k);
            //this->AMK_Pairwise(temp, k);
            //this->General(temp, k, BINARY);
        }
    }

    std::cout << "BETWEEN MDPS" << std::endl;



    // Pour chaque groupe, pour chaque musicien il joue AMO(instrument)
    for (int i = 0; i < card_c; i++)
    {
        for (int j = 0; j < card_a; j++)
        {
            VECT_UINT temp;
            for (int k = 0; k < card_b; k++)
            {
                temp.push_back(abc_variables[ (j*card_b*card_c) + (k*card_c) + i ]);
                std::cout << "a : " << card_c << " " << card_a << " " << card_b<<std::endl;// << "b : " << abc_variables[] << "c : " << abc_variables[] << std::endl;
            }
            unsigned int k = 1;
            //this->ALO(temp, g_variables[i]);
            this->Binary(temp, k);
            //this->AMK_Pairwise(temp, k);
            //this->General(temp, k, BINARY);
        }
    }


    this->s.ToDimacs(dimacs_file);

    system(("./MiniSat_v1.14_linux " + dimacs_file + " " + out_file_name).c_str());

    SolutionInterpreter x;
    x.Interpret(out_file_name, card_a, card_b, card_c, abc_variables);
}


void Problem::RunQ3(string in_file_name, string dimacs_file, string out_file_name)
{
    Parser p;
    p.Parsing2(in_file_name);
    TABLE_BOOL initial_info = p.GetMatrix();

    int card_a = initial_info.size();
    int card_b = initial_info[0].size();
    int card_c = p.GetNbGroups();

    VECT_UINT maximum_groups = p.GetMaxGroups();



    // Exclusion des AB
    VECT_UINT ab_variables;
    this->GenerateVariables(ab_variables, card_a*card_b);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ab;
        for(int j = 0 ; j<card_b ; j++)
        {
            if (j < card_b)
                sub_ab.push_back( ab_variables[(i*card_b)+j] );
            if (!initial_info[i][j])
                s.AddUnit(Lit(NOT,  ab_variables[(i*card_b)+j] ));
        }
        this->ALO(sub_ab);
    }

    // Exclusions des AC
    VECT_UINT ac_variables;
    VECT_UINT g_variables;
    this->GenerateVariables(ac_variables, card_a*card_c);
    this->GenerateVariables(g_variables, card_c);

    for (int i = 0; i<card_a; i++)
    {
        VECT_UINT sub_ac;
        for(int j = 0 ; j<card_c ; j++)
        {
            sub_ac.push_back( ac_variables[(i*card_c)+j] );
            this->s.AddBinary(Lit(IS, g_variables[j]), Lit(NOT, ac_variables[(i*card_c)+j]));
        }
        this->ALO(sub_ac);
        this->Binary(sub_ac, maximum_groups[i]);
    }



    VECT_UINT abc_variables;
    this->GenerateVariables(abc_variables, card_a*card_b*card_c);

    // (abc <-> ab ^ ac)
    for (int i = 0; i < card_a; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            for (int k = 0; k < card_c; k++)
            {
                VECT_LIT temp_one;
                temp_one.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_one.push_back(Lit(IS, ab_variables[ (i*card_b)+j ]));
                VECT_LIT temp_two;
                temp_two.push_back(Lit(NOT, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_two.push_back(Lit(IS, ac_variables[ (i*card_c)+k ]));
                VECT_LIT temp_three;
                temp_three.push_back(Lit(IS, abc_variables[ (i*card_b*card_c) + (j*card_c) + k ]));
                temp_three.push_back(Lit(NOT, ab_variables[ (i*card_b)+j ]));
                temp_three.push_back(Lit(NOT, ac_variables[ (i*card_c)+k ]));
                this->s.AddClause(temp_one);
                this->s.AddClause(temp_two);
                this->s.AddClause(temp_three);
            }
        }
    }

    // Pour chaque groupe, pour chaque instrument joué dans le groupe, il y a alo(mussicien) et amo(musicien)
    for (int i = 0; i < card_c; i++)
    {
        for (int j = 0; j < card_b; j++)
        {
            VECT_UINT temp_complete;
            VECT_UINT temp_condition;
            for (int k = 0; k < card_a; k++)
            {
                temp_complete.push_back(abc_variables[ (k*card_b*card_c) + (j*card_c) + i ]);
                if (j < card_b-1)
                    temp_condition.push_back(abc_variables[ (k*card_b*card_c) + (j*card_c) + i ]);
            }
            unsigned int k = 1;
            this->ALO(temp_complete, g_variables[i]);
            this->Binary(temp_condition, k);
        }
    }

    // Pour chaque groupe, pour chaque personne il ne joue que d'un instrument
    for (int i = 0; i < card_c; i++)
    {
        for (int j = 0; j < card_a; j++)
        {
            VECT_UINT temp;
            for (int k = 0; k < card_b-1; k++)
            {
                temp.push_back(abc_variables[ (j*card_b*card_c) + (k*card_c) + i ]);
            }
            unsigned int k = 1;
            this->Binary(temp, k);
        }
    }


    this->s.ToDimacs(dimacs_file);

    system(("./MiniSat_v1.14_linux " + dimacs_file + " " + out_file_name).c_str());

    SolutionInterpreter x;
    x.Interpret(out_file_name, card_a, card_b, card_c, abc_variables);
}



/*
	* Generating new k variables into v
 */
void Problem::GenerateVariables(VECT_UINT &v, int k)
{
    for (int i = 0; i < k; i++)
    {
        v.push_back(s.GenerateNewVar());
    }
}



/*
	* Bimander main function
	* v: variables needing amk
	* k: at most parameter
	* group_factor: parameter for m value
 */

void Problem::General(VECT_UINT &variables, unsigned int &k, unsigned int group_factor)
{
    std::cout << "Welcome to GENERAL" << std::endl;
    // Setting m value - m is the number of groups created with the vraiables set
    unsigned int m = 0;
    if (group_factor == NOVERTWO) m = ceil((float)variables.size()/2);
    else if (group_factor == SQRTOFN) m = ceil(sqrt(variables.size()));
    else if (group_factor == PAIRWISE) m = 1;
    else if (group_factor == BINARY) m = variables.size();

    unsigned int nb_elem = ceil( (float)variables.size()/m );									// Number of element in each group

    // Creating m groups of size nb_elem and creating clauses for pairwise amk in each group
    TABLE_UINT groups;
    for (int i = 0; i < m; i++)
    {
        VECT_UINT temp;
        for (int j = 0; j < nb_elem ; j++)
        {
            if ((i*nb_elem)+j < variables.size())												// Last group might be composed of less than nb_elem
                temp.push_back(variables[(i*nb_elem)+j]);
        }
        this->AMK_Pairwise(temp, k);

        groups.push_back(temp);
    }

    unsigned int upper_log_m = ceil(log2(m));

    // Generating the clauses for binary encoding between groups for k
    if (k!=1)
        BimanderBinaryK(m, nb_elem, k, upper_log_m, variables);
    else
        BimanderBinaryO(m, nb_elem, k, upper_log_m, variables);

}

void Problem::BimanderBinaryK(unsigned int m, unsigned int nb_elem, unsigned int k, unsigned int upper_log_m, VECT_UINT &variables)
{
    // unsigned int upper_log_n = ceil(log2(variables.size()));

    VECT_UINT binary_variables;
    this->GenerateVariables(binary_variables, k*upper_log_m);

    for (int i = 1; i <= m; i++)
    {
        VECT_UINT temporary_variables;
        this->GenerateVariables(temporary_variables, k);
        for (int h = 1; h <= nb_elem; h++)
        {
            if (((i-1)*nb_elem)+(h-1) < variables.size())
            {
                VECT_LIT prime_clause;
                prime_clause.push_back(Lit(NOT, variables[ ((i-1)*nb_elem)+(h-1) ]));
                FOR_VECT(VECT_UINT, x, temporary_variables)
                {
                    prime_clause.push_back(Lit(IS, (*x)));
                }

                this->s.AddClause(prime_clause);

                for (int l = 1; l <= k; l++)
                {
                    for (int j = 1; j <= upper_log_m; j++)
                    {
                        VECT_LIT sec_clause;
                        sec_clause.push_back(Lit(NOT, temporary_variables[ (l-1) ]));
                        if (i & (1<<(j-1)))
                        {
                            sec_clause.push_back(Lit(IS, binary_variables[ ((l-1)*upper_log_m)+(j-1) ]));
                        }
                        else
                        {
                            sec_clause.push_back(Lit(NOT, binary_variables[ ((l-1)*upper_log_m)+(j-1) ]));
                        }
                        this->s.AddClause(sec_clause);
                    }
                }
            }
        }
    }
}

void Problem::BimanderBinaryO(unsigned int m, unsigned int nb_elem, unsigned int k, unsigned int upper_log_m, VECT_UINT &variables)
{
    // unsigned int upper_log_n = ceil(log2(variables.size()));
    // Generating the Boolean extra variables for binary encoding between groups
    VECT_UINT binary_variables;
    this->GenerateVariables(binary_variables, upper_log_m);
    for (int i = 1; i <= m; i++)
    {
        for (int h = 1; h <= nb_elem; h++)
        {
            for (int j = 1; j <= upper_log_m; j++)
            {
                if (((i-1)*nb_elem)+h-1 < variables.size())
                {
                    VECT_LIT temp;
                    temp.push_back(Lit(NOT, variables[((i-1)*nb_elem)+h-1] ));
                    if (i &  (1<<(j-1)))															// Tests if jth bit of i-1 is 1
                        temp.push_back(Lit(IS, binary_variables[ j-1 ] ));
                    else
                        temp.push_back(Lit(NOT, binary_variables[ j-1 ] ));
                    this->s.AddClause(temp);
                }
            }
        }
    }
}

void Problem::Binary(VECT_UINT &variables, unsigned int &k)
{
    unsigned int n = variables.size();
    unsigned int upper_log_n = ceil(log2(n));

    VECT_UINT binary_variables;
    this->GenerateVariables(binary_variables, k*upper_log_n);

    for (int i = 0; i < n; i++)
    {
        VECT_UINT temporary_variables;
        this->GenerateVariables(temporary_variables, k);

        VECT_LIT prime_clause;
        prime_clause.push_back(Lit(NOT, variables[i]));
        FOR_VECT(VECT_UINT, x, temporary_variables)
        {
            prime_clause.push_back(Lit(IS, (*x)));
        }
        this->s.AddClause(prime_clause);


        for (int g = 0; g < k; g++)
        {
            for (int j = 0; j < upper_log_n; j++)
            {
                VECT_LIT sec_clause;
                sec_clause.push_back(Lit(NOT, temporary_variables[g]));
                if ((i+1) & (1<<(j)))
                {
                    sec_clause.push_back(Lit(IS, binary_variables[ ((g)*upper_log_n)+(j) ]));
                }
                else
                {
                    sec_clause.push_back(Lit(NOT, binary_variables[ ((g)*upper_log_n)+(j) ]));
                }
                this->s.AddClause(sec_clause);
            }
        }
    }
}

void Problem::ALO(VECT_UINT &variables, unsigned int c_value)
{
    //Adding ALO clause
    VECT_LIT alo;
    FOR_VECT(VECT_UINT, i, variables)
    {
        alo.push_back( Lit(IS, (*i)) );
    }
    if (c_value != 0)
        alo.push_back(Lit(NOT, c_value));
    this->s.AddClause(alo);
}


/*
	* AMK Pairwise implementation
	* variables: variables for AMK
	* k: at most k
 */
void Problem::AMK_Pairwise(VECT_UINT &variables, unsigned int &k)
{
    std::cout << "K " << k << std::endl;
    // Adding exclusions for AMK
    if (variables.size() >1 && k<variables.size())
    {

        FOR_VECT(VECT_UINT, j, variables)
        {
            std::cout << (*j) << " ";
        }
        std::cout << std::endl;
        TABLE_LIT amk = this->RecursivePairing(k+1, 0, variables);								// Exclusion clauses are non-ordered subset of size k

        FOR_TABLE(TABLE_LIT, i, amk)
        {
            this->s.AddClause((*i));
        }
        std::cout << "OUT" << std::endl;
    }
}

/*
	* Create all subset of given size non ordered with a set of variables (recursive)
	* top_offset: size of subset
	* val: current value to add to subset
	* variables : set of variables
 */
TABLE_LIT Problem::RecursivePairing(unsigned int top_offset, unsigned int val, VECT_UINT &variables)
{
    if (top_offset == 0) {
        TABLE_LIT sub_res;
        VECT_LIT elem;
        elem.push_back(Lit(NOT, variables[val-1]));
        sub_res.push_back(elem);
        return sub_res;
    }
    TABLE_LIT temp;
    for (int i = val+1; i <= (variables.size() - top_offset)+1; i++)
    {
        TABLE_LIT returned = RecursivePairing(top_offset-1, i, variables);
        if (val!=0)
        {
            FOR_TABLE(TABLE_LIT, j, returned)
            {
                (*j).push_back(Lit(NOT, variables[val-1]));
            }
        }
        temp.insert(temp.end(), returned.begin(), returned.end());
    }
    return temp;
}
