# OLAP

## MDX

<http://en.wikipedia.org/wiki/MultiDimensional_eXpressions>

The query language used for OLAP databases.

De facto standard introduced by Microsoft in 1998.
Not specified by a standards organization,
but appears to have many highly compatible implementations.

## OLTP

<http://en.wikipedia.org/wiki/Online_transaction_processing>

The opposite of OLAP: what MySQL and other relational database do well.

TODO

## OLAP vs OLTP

OLTP systems are more focused on maintaining the current state of the system,
to inform end users, while OLAP is more useful to store
and analyse large quantities of historical data for business analysts.

As a result:

- OLTP serves small chunks of data faster
- OLAP deals better with large amounts of data

## MOLAP

<http://en.wikipedia.org/wiki/MOLAP>

"True OLAP": generally requires a specialized database backend.

Faster since more specialized.

## ROLAP

"Fake OLAP": uses a regular database backend like MySQL with very well constructed tables.

## HOLAP

<http://en.wikipedia.org/wiki/HOLAP>

MOLAP ROLAP hybrid.

## Implementations

<http://en.wikipedia.org/wiki/Comparison_of_OLAP_Servers>

Likely the most popular one in 2014 is Mondrian, but it's not trivial to install on Linux.

Oracle's can be downloaded for free: <http://www.oracle.com/technetwork/database/options/olap/olap-downloads-098860.html>

## Multiple dimensions

Relational databases deal only with two dimensional data: tables.

OLAP however can deal with multiple dimensions:
the basic data structure is then called a cube.
More precisely it is a hypercube since N-dimensional.

## Concept Hierarchy

OLAP give more focus to concept hierarchies, e.g., being easily able to group cities into countries.

## Concepts

### Dimension

Analogous of a group of relational columns, e.g. a country or a city.

### Measure

The lowest level dimension, which contains the smallest division of data measure, i.e. numbers.

For example, it could be a City if the city is the smallest division in our database,
or a streets, households, etc.

### Member

Cell in a relational database.

## OLAP operations

There are 4 basic OLAP operations:

- Roll-up
- Drill-down
- Slice and dice
- Pivot (rotate)

### Roll-up

Group cities into countries.

Reduces the number of dimensions by combining related elements of a hierarchy.

### Drill-down

Reverse of roll-up.

### Dice

### Slice

Select a sub-cube from the cube.

Slice is for selecting a single dimension.

### Pivot
