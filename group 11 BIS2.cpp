#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

const int N = 20;


string districts[N] = {
    "Blantyre", "Nsanje", "Chikwawa", "Phalombe",
    "Thyolo", "Mwanza", "Chiradzulu", "Zomba",
    "Balaka", "Machinga", "Mangochi", "Mulanje",
    "Ntcheu", "Dedza", "Lilongwe", "Dowa",
    "Ntchisi", "Kasungu", "Salima", "Nkhotakota"
};


vector<pair<int, int>> graph[N];//weight and shortest path

// Function to connect two districts
void addRoad(int u, int v, int distance)
{
    graph[u].push_back({v, distance});
    graph[v].push_back({u, distance});		
    
}


string toLowerCase(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        name[i] = tolower(
            static_cast<unsigned char>(name[i])
        );
    }

    return name;
}

int findDistrict(string name)
{
    name = toLowerCase(name);

    for (int i = 0; i < N; i++)







    {
        if (toLowerCase(districts[i]) == name)
        {
            return i;
        }
    }

    return -1;
}


void dijkstra(int source, vector<int>& dist,
              vector<int>& parent)
{
    const int INF = numeric_limits<int>::max();

    dist.assign(N, INF);
    parent.assign(N, -1);

    // Priority queue stores distance and district index
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;

        pq.pop();

        // Ignore outdated entries
        if (currentDistance != dist[currentNode])
        {
            continue;
        }

        
        for (int i = 0;
            i < graph[currentNode].size(); i++)
        {
            int neighbour = graph[currentNode][i].first;
            int weight = graph[currentNode][i].second;

            int newDistance = currentDistance + weight;

            
            if (newDistance < dist[neighbour]) //update if shorter path is found
            {
                dist[neighbour] = newDistance;
                parent[neighbour] = currentNode;

                pq.push({newDistance, neighbour});
            }
        }
    }
}

// Display the shortest path to one destination
void showOnePath(int source, int destination,
                 const vector<int>& dist,
                 const vector<int>& parent)
{
    const int INF = numeric_limits<int>::max();

    cout << "\n----------------------------------\n";
    cout << "          SHORTEST ROUTE\n";
    cout << "------------------------------------\n";

    cout << "Starting district: " 
         << districts[source] << "\n";

    cout << "Destination: "
         << districts[destination] << "\n";

    if (dist[destination] == INF)
    {
        cout << "No route exists to this destination.\n";
        return;
    }

    // Reconstruct the shortest path
    vector<int> path;

    for (int node = destination;
         node != -1;
         node = parent[node])
    {
        path.push_back(node);
    }

    reverse(path.begin(), path.end());

    cout << "Shortest path: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << districts[path[i]];

        if (i < path.size() - 1)
        {
            cout << " -> ";
        }
    }

    cout << "\nTotal distance: "
         << dist[destination] << " km\n";

    cout << "-----------------------------------\n";
}


void showAllPaths(int source,
                  const vector<int>& dist,
                  const vector<int>& parent)
{
    const int INF = numeric_limits<int>::max();

    cout << "\n----------------------------------\n";
    cout << " ALL SHORTEST PATHS FROM BLANTYRE\n";
    cout << "------------------------------------\n";

    for (int destination = 0;
         destination < N;
         destination++)
    {
        cout << "\nDestination: "
             << districts[destination] << "\n";

        if (dist[destination] == INF)
        {
            cout << "No route available.\n";
            continue;
        }

        
        vector<int> path;

        for (int node = destination;
             node != -1;
             node = parent[node])
        {
            path.push_back(node);
        }

        reverse(path.begin(), path.end());

        cout << "Shortest path: ";

        for (int i = 0; i < path.size(); i++)
        {
            cout << districts[path[i]];

            if (i < path.size() - 1)
            {
                cout << " -> ";
            }
        }

        cout << "\nTotal distance: "
             << dist[destination] << " km\n";
    }

    cout << "\n-------------------------------------\n";
}

int main()
{
    
    // ROAD CONNECTIONS AND WEIGHTS 
    

    addRoad(1, 2, 123);   // Nsanje - Chikwawa
    addRoad(0, 2, 45);    // Blantyre - Chikwawa
    addRoad(0, 3, 90);    // Blantyre - Phalombe
    addRoad(0, 4, 34);    // Blantyre - Thyolo
    addRoad(0, 5, 95);    // Blantyre - Mwanza
    addRoad(0, 6, 25);    // Blantyre - Chiradzulu
    addRoad(0, 7, 65);    // Blantyre - Zomba
    addRoad(0, 8, 135);   // Blantyre - Balaka

    addRoad(8, 9, 50);    // Balaka - Machinga
    addRoad(9, 7, 50);    // Machinga - Zomba
    addRoad(9, 10, 75);   // Machinga - Mangochi

    addRoad(4, 11, 32);   // Thyolo - Mulanje
    addRoad(11, 3, 45);   // Mulanje - Phalombe

    addRoad(6, 7, 40);    // Chiradzulu - Zomba
    addRoad(8, 12, 55);   // Balaka - Ntcheu
    addRoad(12, 13, 75);  // Ntcheu - Dedza

    addRoad(14, 13, 85);  // Lilongwe - Dedza
    addRoad(14, 15, 50);  // Lilongwe - Dowa
    addRoad(14, 16, 110); // Lilongwe - Ntchisi
    addRoad(14, 17, 130); // Lilongwe - Kasungu
    addRoad(14, 18, 98);  // Lilongwe - Salima

    addRoad(15, 18, 100); // Dowa - Salima
    addRoad(18, 19, 112); // Salima - Nkhotakota
    addRoad(19, 17, 135); // Nkhotakota - Kasungu

    

    int source = 0; // representing Blantyre

    vector<int> dist;
    vector<int> parent;

    dijkstra(source, dist, parent);

    int option;

    do
    {
        cout << "\n------------------------------------\n";
        cout << "  MALAWI SHORTEST ROUTE SYSTEM\n";
        cout << "--------------------------------------\n";
        cout << "Starting point is Blantyre (BT)\n";

        cout << "1. Find shortest path to one district\n";
        cout << "2. Show ALL shortest paths from Blantyre\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        

        if (!(cin>>option))
        {
        	cout<<"invalid input. please enter a number.\n";
        	
        	cin.clear();
        	cin.ignore(1000,'\n');
        	
        	continue;
		}
        
        if (option == 1)
        {
            cout << "\nAvailable districts:\n";

            for (int i = 0; i < N; i++)
            {
                cout << i + 1 << ". "
                     << districts[i] << "\n";
            }

            string destinationName;

            cout << "\nEnter destination district name: ";
            
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
        
            getline(cin, destinationName);

            int destination = findDistrict(destinationName);

            if (destination == -1)
            {
                cout << "Invalid district name. "
                     << "Please try again.\n";
            }
            else
            {
                showOnePath(
                    source, destination, dist, parent
                );
            }
        }

        
        
        else if (option == 2)
        {
            showAllPaths(source, dist, parent);
        }
        else if (option == 3)
        {
            cout << "Thank you for using the system.\n";
        }
        else
        {
            cout << "Invalid option. "
                 << "Please select 1, 2, or 3.\n";
        }

    } while (option != 3);

    return 0;
}