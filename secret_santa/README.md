Secret Santa
============

This is a program to draw Secret Santa names for an extended family made up of
several nuclear families.  I wrote this sitting in my in-laws' kitchen after
watching my wife and mother-in-law spend half an hour writing people's names on
scraps of paper and trying to draw names according to the rules of the draw:

1. Members of a nuclear family may not draw each other (because they typically
   already give gifts to each other already)
2. A person may not get themself (for reasons which should be obvious)
3. A person may not get their own Secret Santa (e.g. Alice cannot get Bob if
   Bob has Alice; this is somewhat arbitrary, but generally fine)

After about an hour of writing code and testing, they were on their fourth or
fifth attempt at performing the draw, because you can run out of possible family
members for a particular person due to the exclusion rules.  Meanwhile, I had
finished the code and performed the drawing for them.

This code has gone through some revisions over the past few years, but is mostly
pretty similar to what I wrote in an hour and a half in 2012.  I mention the
time it took to write not to boast, but to emphasize that this is an example of
quick-and-dirty problem solving code as opposed to finely tuned production code,
and the level of quality, optimization etc. is not suited to the level of e.g.
a web service, but is perfectly suited for its intended purpose.


Examples
--------

An example family file as well as a previous-year results file and the
accompanying map file are present in the repository as an example.  In the
provided example, Steve has married Barbara and they have decided to operate as
a unit (providing the mapping `Steve -> Steve and Barbara`), and Tom has become
Voldemort (providing the mapping `Tom -> Voldemort`).  The family file is up to
date, while the previous year's results reflect the previous year's family
composition; the mapping file provides the link between the two so that e.g.
Voldemort (formerly Tom) will not be matched with the same person he was matched
with last year.

Both family and mapping files are standard CSV files, with leading spaces after
the comma delimiter stripped (allowing for slightly prettier files).  The match
input file format is equal to the output format of the script, allowing the
output to be piped directly to a file to be saved as the previous year input for
the next year (which could be run most conveniently as
`secret_santa.py test_family.csv | tee test_family_results-2016`).


Notes
=====

There have been a few revisions to the code in response to family feedback, and
there are a number of optimizations that could be made to improve run time,
behavior, and asymptotic complexity.


Updates
-------

- On the second year, a few people pointed out that they had been matched with
  the same person they had on the previous year.  A mechanism for reading in the
  output of the previous year to eliminate the previous year's matches was
  added.

- On the third year, the problem appeared to remain, despite the fact that the
  fix had been otherwise verified.  The secondary problem was that when some
  family units changed (primarily due to marriage or additional children), the
  names (used for eliminating matches) would no longer match.  A mapping
  facility was added to specify name changes from drawing to drawing so that the
  previous year's matches would still carry forward.


Potential improvements
----------------------

As mentioned previously, this code is "quick and dirty" and was written for
quick execution of a purpose.  Run interactively on small groups, the program
runs quicky enough as to appear instantaneous.  However, if this were to be made
into a web service scaling to thousands of simultaneous users, there are parts
which might end up considerably increasing run time or resource utilization
which could be optimized, and elements which could be changed to improve
usability:

- The list of possible matches for each user is generated via a copy of a
  potentially large dictionary (`available_people = dst_pool.copy()`) for each
  person; a more efficient arrangement (such as maintaining a single
  dictionary/set of available matches and restoring items removed for
  person-specific exclusions) would result in a lot less copying, as well as a
  better asymptotic time bound.  This would take a moderate amount of time and
  require good testing to ensure that replacements are handled correctly in
  corner cases.

- The choice itself is made via `random.choice(list(available_people.keys()))`,
  which was quick to write up but is O(n) time (and a long O(n) at that) to
  execute.  That could be made much faster by mapping to a constant-time access
  data structure instead of a list.

- If the algorithm runs out of available matches for a user, it just terminates
  and requires the user to run it again.  Running interactively, this is fine,
  as the user just has to run repeatedly until a list is generated.  It would be
  trivial to modify the algorithm to run until completion (for a maximum number
  of trials, in case of an impossible situation), but it would be better still
  to run the algorithm semi-deterministically and resolve when a person has only
  a single match left.  This would require a significant rewrite, as currently
  the matches are considered only one person at a time, and it would result in
  time and memory bounds of O(n^2) unless further optimizations simplify the
  problem.  Operating one match at a time while accumulating an exclusion list
  results in time and memory bounds of O(n), with the possibility that the trial
  must be re-run occasionally.

- There is no formal set of tests and relatively little documentation (a normal
  casualty of the quick-and-dirty project that nonetheless must be rectified for
  production code if the transition is ever made).

- The code is run essentially in a classic scripting mode, rather than as a
  structured, hierarchical program.  This would make it considerably harder to
  embed within any kind of service.  It wouldn't take a lot to break it up into
  functions and add unit tests (e.g. through `nose2`).

- Output is a non-standard text format originally intended to be pasted directly
  to an email, and input formats are CSV.  For embedding within a service, the
  ability to accept and output more standard interchange formats (such as JSON)
  would be useful.

- There is little to no validation of the input; the biggest problem here (since
  almost nothing will make this go truly off the rails) is that if someone's
  name has changed and the change is accidentally left out of the match file,
  there is no warning to reflect this (this is, in fact, valid in the case where
  someone has tragically departed the family, but it should be noted at least as
  a diagnostic, or there should be a mechanism for reporting this in the mapping
  file).
