/*
  Name - Aayush Tyagi
  Section - A
  Roll no. - 03
  University roll no. - 2013206
*/
//                            PROJECT DFA MINIMIZER
/*                                        Method: Myhill-Nerode Theorem
Algorithm
Step 1:  Make a table taking all states of N*N where N is number of states

Step 2: Mark all pairs which are one final and other non-final

Step 3: Repeat step 2 until we cannot mark anymore states ALso If there is any unmarked pair, mark it if the pair {δ (qi, A), δ (qi, A)} is marked for some input alphabet.

Step 4: Take all unmarked pair and combine them to single state
*/



#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;


struct node
{
    int NEXT1;
    char alphabet;
    int NEXT2;
};

void algoritm(vector <int> state, int state_count, vector<int> final_states, int N_Finals, vector<node> Function, int N_transition, vector <char> alphabets, int n_alphabet)
{
    int table[state_count][state_count];
            for(int i = 0; i < state_count;i ++)
                for(int j = 0; j < state_count;j ++)
                {
                    if(j >= i)
                        table[i][j] = -1;
                    else
                        table[i][j] = 0;
                }


// We mark all the pairs (NEXT1, NEXT2) with prop that the 2 states are not both final or non-final

    char check; // Count how many of the states in the current pair are final. If there is only 1 then it must be marked in the table;
    for(int i = 0; i < state_count; i ++)
        for(int j = 0; j < i; j ++)
        {
            check = 0;
            for(int k = 0; k < N_Finals; k ++)
                if(final_states[k] == i || final_states[k] == j)
                    check ++;
            if(check == 1)
                table[i][j] = 1;
        }


    bool flag;
    do
    {
        flag = false;
        for(int i = 0;i < state_count;i ++)
        for(int j = 0;j < i;j ++)
            {
                if(table[i][j] == 0)
                {
                    for(int k = 0;k < n_alphabet;k ++)
                    {
                        int p1, p2;
                        char a = alphabets[k];
                        for(int x = 0;x < N_transition; x ++)
                        {
                            if(Function[x].alphabet == a && Function[x].NEXT1 == i)
                                p1 = Function[x].NEXT2;
                            if(Function[x].alphabet == a && Function[x].NEXT1 == j)
                                p2 = Function[x].NEXT2;
                        }
                        if(table[p1][p2] == 1 || table[p2][p1] == 1)
                        {
                            table[i][j] = 1;
                            flag = true;
                            break;
                        }

                    }
                }
            }

    }while(flag == true);


// The pairs in the table that are not marked represent the states that can be joined
    // We create the pairs of states, and we bring them together to form a larger state

    // We will use a matrix to concatenate the states, so that each line
    // represents a state, and each column represents a state from the initial state

    int table_state[state_count][state_count], ki, kj, p1, p2, f[100] = {0};

    for(int i = 0; i < state_count;i ++)
    for(int j = 0;j < state_count;j ++)
        table_state[i][j] = -1;

    for(int i = 0; i < state_count;i ++)
    for(int j = 0; j < i;j ++)
        {
            flag = false;
            if(table[i][j] == 0)
            {
                ki = 0;
                kj = 0;
                p1 = -1;
                p2 = -1;
                for(ki = 0; ki < state_count && table_state[ki][0] != -1; ki ++)
                {
                    for(kj = 0; kj < state_count && table_state[ki][kj] != -1 ;kj ++)
                    {
                        if(table_state[ki][kj] == i)
                        {
                            p1 = j;
                            flag = true;
                        }
                        if(table_state[ki][kj] == j)
                        {
                            p2 = i;
                            flag = true;
                        }

                    }
                    if(p1 != -1 && p2 != -1)
                    {
                        continue;
                    }
                    else if(p1 != -1)
                        {
                            table_state[ki][kj] = p1;
                            f[p1] ++;
                        }
                    else
                        {
                            table_state[ki][kj] = p2;
                            f[p2] ++;
                        }
                }
                if(flag == false)
                {
                    table_state[ki][0] = i;
                    table_state[ki][1] = j;
                    f[i] ++;
                    f[j] ++;
                }
            }
        }

        for(ki = 0; table_state[ki][0]!= -1; ki++);

        for(int i = 0; i < state_count; i++)
            if(f[i] == 0)
            {
                table_state[ki][0] = i;
                ki ++;
            }

        int finale[100] = {0}, i1;
        for(int i = 0; i < state_count && table_state[i][0] != -1; i ++)
        for(int j = 0; j < state_count && table_state[i][j] != -1; j ++)
        for(int k = 0; k < N_Finals; k ++)
            if(table_state[i][j] == final_states[k])
                finale[i] = 1;

        cout << "statele rezultate sunt: ";
        for(int i = 0; i < state_count && table_state[i][0] != -1;i ++)
        {
            for(int j = 0; j < state_count && table_state[i][j] != -1; j ++)
                cout << table_state[i][j];
            cout << " ";
        }

        /*cout << endl << endl;
        cout << "Starile initiale sunt: ";
        for(int i = 0; i < nr_stari && matrice_stari[i][0] != -1; i ++)
        {
            for(int j = 0; j < state_count && matrice_state[i][j] != -1; j ++)
                if(finale[i] == 0)
                    cout << matrice_state[i][j];
            cout << " ";
        }*/

        cout << endl << endl;
        cout << "Starile finale sunt: ";
        bool printed;
        for(int i = 0; i < state_count && table_state[i][0] != -1; i ++)
        {
            printed = false;
            for(int j = 0; j < state_count && table_state[i][j] != -1; j ++)
                if(finale[i] == 1)
                {
                    cout << table_state[i][j];
                    printed = true;
                }

            if(printed)
                cout << " ";
        }

        cout << endl << endl;
        cout << "MINIMISED DFA: " << endl;
        for(int i = 0; i < state_count; i ++)
        for(int k = 0; k < n_alphabet; k ++)
        for(int j = 0; j < N_transition; j ++)
            if(table_state[i][0] == Function[j].NEXT1 && alphabets[k] == Function[j].alphabet)
            {
                for(int x = 0; table_state[i][x] != -1; x ++)
                    cout << table_state[i][x];
                cout << " " << alphabets[k] << " ";
                flag = 0;
                for(i1 = 0; i1 < state_count && table_state[i1][0] != -1 && flag == 0; i1 ++)
                for(int j1 = 0; j1 < state_count && table_state[i1][j1] != -1; j1 ++)
                    if(table_state[i1][j1] == Function[j].NEXT2)
                    {
                        flag = 1;
                        break;
                    }

                for(int j1 = 0; table_state[i1-1][j1] != -1; j1 ++)
                    cout << table_state[i1-1][j1];
                cout << endl;
                break;
            }
}
int main()
{
    cout << "\t\t\t +----------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t |                                DFA MINIMIZER                               |" << endl;
    cout << "\t\t\t +----------------------------------------------------------------------------+" << endl;
    cout << endl << endl;

    int n_state, n_alphabet, initial_state, N_transition, N_final;
    vector <int> states,final_state;
    vector <char> alphabets;
    vector <node> transition;
    cout<<"Enter number of states:";
    cin>>n_state;
    int x;char c;
    cout<<"Enter states:";
     for(int i = 0; i < n_state; i ++)
    {
        cin >> x;
        states.push_back(x);
    }
    cout<<"Enter number of alphabets:";
    cin>>n_alphabet;
    cout<<endl<<"Enter alphabets:";
    for(int i = 0; i < n_alphabet;i ++)
    {
        cin >> c;
        alphabets.push_back(c);
    }
    cout<<"Enter number of Final states :";
    cin>>N_final;
    cout<<"Enter Final States:";
        for(int i = 0; i < N_final; i ++)
    {
        cin >> x;
        final_state.push_back(x);
    }
    int i=0;
     N_transition=n_state * n_alphabet;
    initial_state=states[0];
    cin.ignore();
    node a;
    cout << "Enter State Transition Table:\n";
    cout << "Alphabet | \t" ;
    for(auto i=alphabets.begin() ; i!=alphabets.end() ; i++)
        cout << *i << " " ;
    cout<<endl;

    for(auto i=states.begin() ; i != states.end() ;i++)
    {
        cout << "State-";
        cout<<*i;
        cout<<"|\t";
        a.NEXT1=*i;
        for(auto j=alphabets.begin(); j  != alphabets.end(); j++)
        {
            a.alphabet=*j;
            cin>>a.NEXT2;
            cin.ignore();
            transition.push_back(a);
        }
    }

    //Remove Unreachable node
    cout<<"Checking Unreachable State..";
    int flag=0;
    for(auto i=states.begin()+1;i!=states.end();i++)
    {
        flag=0;
        for(auto j=transition.begin();j!=transition .end();j++)
        {
            if(j->NEXT1 !=(*i) && j->NEXT2==(*i))
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<endl<<"Removing :"<<(*i);
            //removing state
            states.erase(i);
            //removing from transition table
        for(auto j=transition.begin();j!=transition .end();j++)
        {
            if(j->NEXT1 ==(*i))
            {
                transition.erase(j);
            }
        }
        i=states.begin();
            n_state--;
            N_transition=n_state * n_alphabet;

        }
    }
            algoritm(states, n_state, final_state, N_final, transition, N_transition, alphabets, n_alphabet);

    return 0;
}
