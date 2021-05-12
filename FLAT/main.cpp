#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

char DFA[99][99];


int main()
{
    char Q[99], p, sigma[99], F[99], Transitions[99], trans, finalq, startq, inputstr[99], traversedq[99], newstate, acc, eps= '/';
    int i, j, k, nq, nsigma, trok, starti, newi, ok = 1, okk = 0;

    cout<<"Enter the number of states for the DFA: ";
    cin>>nq;
    cout<<endl;
    cout<<"Enter the number of symbols the alphabet: ";
    cin>>nsigma;
    cout<<endl;
    cout<<"Enter the symbols in the alphabet: ";
    for (i=0;i<nsigma;i++)
        cin>>sigma[i];
    cout<<endl;
    cout<<"Do you need one of the states to be a trash state? (0 for no, 1 for yes): ";
    cin>>trok;
    cout<<endl;

    for (i=0;i<=nq;i++)
    {
        DFA[i+1][0] = 'A' + i;
    }
    if (trok==1)
        DFA[nq][0] = 'T';

    for (i=0;i<=nsigma;i++)
        DFA[0][i+1] = sigma[i];

    cout<<"The states are: ";
    for (i=0;i<nq;i++)
        if (i == nq-1)
            cout<<DFA[i+1][0]<<"; ";
        else
            cout<<DFA[i+1][0]<<", ";

    cout<<endl;
    cout<<"Enter the final states (type . to end the input): ";
    for (i=0;i<nq&&finalq!='.';i++)
    {
        cin>>finalq;
        F[i] = finalq;
    }
    cout<<endl;
    cout<<"Enter the starting state: ";
    cin>>startq;
    cout<<endl;

        for (i=0; i<nq; i++)
        {
            if (trok == 0)
            {
                cout<<"Enter the transitions for "<<char('A'+ i)<<endl;
                for (j=0;j<nsigma;j++)
                {
                    cout<<char('A' + i)<<" --"<<DFA[0][j+1]<<"--> ";
                    cin>>trans;
                    DFA[i+1][j+1] = trans;
                }
            }
            else if (trok == 1)
            {
                if (i == nq-1)
                {
                    trans = 'T';
                    for (j=0;j<nsigma;j++)
                        DFA[i+1][j+1] = trans;
                }

                else
                {
                    cout<<"Enter the transitions for "<<char('A'+ i)<<endl;
                    for (j=0;j<nsigma;j++)
                    {
                            cout<<char('A' + i)<<" --"<<DFA[0][j+1]<<"--> ";
                            cin>>trans;
                            DFA[i+1][j+1] = trans;
                    }

                }
            }
        }

    cout<<endl;
    cout<<"The DFA looks like this: "<<endl;
    for (i=0;i<=nq;i++)
    {
        for (j=0;j<=nsigma;j++)
            if (i==0 && j==0)
                cout<<"-"<<"  |  ";
            else
                cout<<DFA[i][j]<<"  |  ";
        cout<<endl;
        for (k=0;k<nsigma;k++)
            cout<<"-------";
        cout<<endl;
    }
    for(i=0;i<=nq;i++)
        if (DFA[i+1][0] == startq)
        {
            starti = i+1;
            break;
        }


    cout<<endl;
    while (ok == 1)
    {
        memset(traversedq, 0, sizeof traversedq);
        okk = 0;
        cout<<"Enter the strings to check their validity: ";
        cin>>inputstr;
        for (k=0;k<strlen(inputstr);k++)
        {

            traversedq[0] = startq;
            if (inputstr[k]=='/')
                continue;

            if (k == 0)
                newi = starti;
            else
                for (i=0;i<nq;i++)
                    if (DFA[i+1][0] == newstate)
                    {
                        newi = i+1;
                        break;
                    }

            for (j=0;j<nsigma;j++)
                if (DFA[0][j+1] == inputstr[k])
                {
                    newstate = DFA[newi][j+1];
                    break;
                }
            traversedq[k+1] = newstate;

        }
        cout<<endl;
        cout<<"The states traversed by the string are: ";
        for (k=0;k<strlen(traversedq);k++)
            if (k == strlen(traversedq)-1)
            {
                acc = newstate;
                cout<<traversedq[k]<<";";
            }
            else
                cout<<traversedq[k]<<", ";
        cout<<endl;
        for (i=0;i<strlen(F);i++)
            if (F[i] == acc)
            {
                cout<<"String accepted"<<endl;
                okk = 1;
                break;

            }
        if (okk == 0)
            cout<<"String rejected"<<endl;

        cout<<"Do you want to read another string? (0 for no, 1 for yes): ";
        cin>>ok;
        cout<<endl;
    }

    return 0;
}
