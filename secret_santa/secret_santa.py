#!/usr/bin/env python3

import random
import sys
import csv

# Get the name of the family to run the drawing for.
try:
    family_filename = sys.argv[1]
except IndexError:
    print("usage: secret_santa.py <family file> [previous result file [map file]]")
    sys.exit(10)

# Try to open the family file.
try:
    family_file = csv.reader(open(family_filename), skipinitialspace=True)
except IOError as e:
    print("Error opening family file %s: %s" % (family_filename, str(e)))
    sys.exit(20)

# Check to see if results for the previous year were supplied.
try:
    last_file = sys.argv[2]
    last_year_list = [z.strip().split(" : ") for z in open(last_file)]
    last_year = dict(filter(lambda x: len(x) > 1, last_year_list))
except IndexError:
    last_year = {}

# Check to see if a map file was provided.
if last_year:
    try:
        name_map = dict(csv.reader(open(sys.argv[3]), skipinitialspace=True))
    except IndexError:
        # If no map file was provided, that's fine, move along.
        name_map = {}
    except IOError as e:
        print("Error opening mapping file %s: %s" % (sys.argv[3], str(e)))
        sys.exit(30)


# Initialize the people with their families.
people = {}
for family in family_file:
    for person in family:
        people[person] = family

assignees = {}

# Make a copy of the pool to delete people from one by one.
dst_pool = people.copy()


for person, family in people.items():
    # Make a copy of the people list.
    available_people = dst_pool.copy()

    # Remove their recipient from last year, if any.
    try:
        # If the person's name is in the map, change it before deleting.
        person_mapped = name_map.get(person, person)

        del available_people[last_year[person_mapped]]
    except KeyError:
        # If not, no worries.  We could get here if either the giver was not on
        # last year's list, or their recipient last year isn't on this year's.
        pass

    # Clear out the family.
    for family_member in family:
        if family_member in available_people:
            del available_people[family_member]

    # Are we out of people?
    if not available_people:
        print("Ran out of available family.  Try again.")
        sys.exit()

    # Assign a random person from the available pool.
    assignee = random.choice(list(available_people.keys()))
    assignees[person] = assignee
    del dst_pool[assignee]
    
max_len = max(20, max([len(x) for x in assignees.keys()]))
for person, assignee in assignees.items():
    print(("%%%ds" % (max_len) + " : %s") % (person, assignee))
