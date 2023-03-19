#include <bits/stdc++.h>

using namespace std;

int dx[] = {0, 0, -1, -1, -1, 1, 1, 1};
int dy[] = {-1, 1, -1, 0, 1, -1, 0, 1};
int countexpand = 0;
int M;
bool flag = false;
int cx=-1,cy=-1;
int putNumbers(int i, int j, vector<vector<char>> &mat, int r, int c)
{
    int numcount = 0;
    for (int x = 0; x < 8; x++)
    {
        int newi = i + dx[x];
        int newj = j + dy[x];
        if (newi >= 0 && newj >= 0 && newi < r && newj < c && mat[newi][newj] == '*')
        {
            numcount++;
        }
    }
    return numcount;
}
void dfs(int i, int j, vector<vector<bool>> &vis, vector<vector<char>> &mat, int r, int c,int t)
{
    if (i < 0 || j < 0 || i >= r || j >= c || vis[i][j] == true || mat[i][j] == '*')
        return;

    vis[i][j] = true;
    countexpand++;
//     cout << countexpand << endl;
    if (countexpand == (r * c) - M)
    {
        if(cx!=-1 && cy!=-1)
        mat[cx][cy]='C';
        cout << "case#"<<t<<": "<<endl;
         for (int i = 0; i < r; i++)
                    {
                        for (int j = 0; j < c; j++)
                        {
                            if(mat[i][j]=='.' ||mat[i][j]=='*'||mat[i][j]=='C')
                            cout << mat[i][j] << " ";
                            else
                            cout<<'.'<<" ";
                        }
                        cout << endl;
                    }
        flag = true;
        return;
    }
    for (int x = 0; x < 8; x++)
    {
        int pn= putNumbers(i, j, mat, r, c); 
        if(mat[i][j]=='C' && pn!=0) return;
        if(mat[i][j]=='C' && pn==0)
            cx=i,cy=j;

        mat[i][j]=pn+'0';
        if ((mat[i][j] == '0' || mat[i][j]=='C') && flag == false)
        {
            int newi = i + dx[x];
            int newj = j + dy[x];
            dfs(newi, newj, vis, mat, r, c,t);
        }
        mat[i][j] = '.';
    }
    }
    // cout << "dfs call:" << i << " " << j << endl;

void config(vector<vector<char>> &mat, int mines, vector<vector<bool>> &mineskept,int t)
{
    int r = mat.size();
    int c = mat[0].size();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (!mineskept[i][j])
            {
                mat[i][j] = '*';
                mines--;
                mineskept[i][j] = true;

                if (mines == 0)
                {
                    for (int x = 0; x < r; x++)
                    {
                        for (int y = 0; y < c; y++)
                        {
                            vector<vector<bool>> vis(r, vector<bool>(c));
                            countexpand = 0;
                            // cout << countexpand << " ";
                            if(mat[x][y]!='*' && flag==false && vis[x][y]==false){
                            mat[x][y]='C';
                            dfs(x, y, vis, mat, r, c,t);
                            mat[x][y]='.';
                            }
                        }
                    }
                }
                if(mines!=0 && flag==false)
                config(mat, mines, mineskept,t);
                mat[i][j] = '.';
                mines++;
                //mineskept[i][j] = false;
            }
        }
    }
}
int main()
{
    freopen("small_input.txt", "r", stdin);
    freopen("output_small.txt", "w", stdout);
    
    int t;
    cin>>t;
    int testcase=1;
    while(t--){
    int r, c, m;
    cin >> r >> c >> m;
    M = m;
    flag = false;
    countexpand = 0;
    cx=-1;
    cy=-1;
    vector<vector<char>> mat(r, vector<char>(c));
    vector<vector<bool>> mineskept(r, vector<bool>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mat[i][j] = '.';
        }
    }
    if(r*c-2==M || r*c<M){
         cout << "case#"<<testcase<<": "<<endl<<"impossible"<<endl;
         testcase++;
         continue;
    }
    config(mat, m, mineskept,testcase);

    if (!flag)
        cout << "case#"<<testcase<<": "<<endl<<"impossible"<<endl;

        testcase++;
    }
    return 0;
}
