#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

// Function to load movie data from CSV
void load_movies(const string& filename, map<int, string>& movies, map<int, string>& genres_map) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << ". Please ensure the file exists.\n";
        exit(1);
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        int movie_id;
        string title, genres;

        getline(ss, line, ',');
        movie_id = stoi(line);
        getline(ss, title, ',');
        getline(ss, genres);

        // Remove the year from the title, assuming it is in the format "(year)"
        size_t year_pos = title.find('(');
        if (year_pos != string::npos) {
            title = title.substr(0, year_pos); // Remove year part
        }

        movies[movie_id] = title;
        genres_map[movie_id] = genres;
    }
    file.close();
}

// Function to get unique genres from the movies
set<string> get_unique_genres(const map<int, string>& genres_map) {
    set<string> unique_genres;
    for (const auto& entry : genres_map) {
        stringstream ss(entry.second);
        string genre;
        while (getline(ss, genre, '|')) {
            unique_genres.insert(genre);
        }
    }
    return unique_genres;
}

// Main function to generate recommendations
int main() {
    map<int, string> movies; // Movie ID -> Title
    map<int, string> genres_map; // Movie ID -> Genres
    map<int, map<int, double>> ratings; // User ID -> (Movie ID -> Rating)

    // Load data from CSV files
    load_movies("movies.csv", movies, genres_map);

    // Get unique genres
    set<string> unique_genres = get_unique_genres(genres_map);

    // Display available genres
    cout << "Available genres:\n";
    int genre_count = 1;
    for (const auto& genre : unique_genres) {
        cout << genre_count++ << ". " << genre << endl;
    }

    string target_genre;
    cout << "\nEnter the genre you want recommendations for: ";
    getline(cin, target_genre);

    // Recommend movies based on genre
    cout << "\nTop 5 recommended movies in genre '" << target_genre << "':\n";
    vector<pair<int, string>> recommended_movies;

    for (const auto& movie : movies) {
        int movie_id = movie.first;
        if (genres_map[movie_id].find(target_genre) != string::npos) {
            recommended_movies.push_back({movie_id, movie.second});
        }
    }

    // Sort recommended movies by their title (optional, can sort by rating if needed)
    sort(recommended_movies.begin(), recommended_movies.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.second < b.second; // Sort alphabetically by title (can modify for rating-based sorting)
    });

    // Print top 5 recommendations
    size_t count = 0;
    for (const auto& movie : recommended_movies) {
        if (count >= 5) break;
        cout << "Movie: " << movie.second << endl;
        count++;
    }

    if (recommended_movies.empty()) {
        cout << "No recommendations found for the genre '" << target_genre << "'.\n";
    }

    return 0;
}
