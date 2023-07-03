# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    print("starting simulation...")
    rating_csv = sys.argv[1]
    #we declare a list where the dictionaries (team,rating)will live
    teams = []
    # TODO: Read teams into memory from file
    with open(rating_csv, "r") as csv_file:
        #open the file and use DictReader to format the csv into a dictionary (each row is a dictionry with keys(header) and values(data from csv))
        file_reader = csv.DictReader(csv_file)
        for row in file_reader:
            #we change from string to int and append it to the list on by one
            row['rating'] = int(row['rating'])
            teams.append(row)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    #while loop we keep going until we run out of opponents
    while len(teams) > 1:
        teams = simulate_round(teams)
    #return the value of team, indexed at 0 because that is the only team left after winning all the rounds
    return teams[0]['team']


if __name__ == "__main__":
    main()
