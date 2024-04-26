# Bacchus Noir Form of Durham input files

* Identifiers in `<...>` are expanded
* Identifiers in `"..."` are free format terminal strings
* Strings in `'...'` are literal tokens (without the single quote)

## The file

    <file>
	  : <header> <datasets> <end>
	  | <datasets> <end>

    <end>
	  : '*E:'

## The header

    <header> 
	  : <header lines>

    <header lines>
	  : <header line>
	  | <header line> <header lines>

    <header line>
	  : '*' <key-value spec>

    <key-value spec>
	  : 'author:' "Upcase last-name of first author"
	  | 'reference:' "journal/archive reference" ':' "year"
	  | 'doi:' "DOI number"
	  | 'cdsId:' "CERN document server  identification number"
	  | 'durhamId:' "Durham submission number"
	  | 'inspireId:' "inSpire identification number"
	  | 'status: Encoded ' "day" ' ' "3 letter month code" ' ' "year"
	    'by' "full name"
	  | 'experiment:' "laboratory" '-' "accelerator" '-' "detector"
	  | 'detector:' "detector"
	  | 'title:' "title of paper"
	  | 'comment:' "laboratory" '-' "accelerator" '.' "abstract"

Note that `"abstract"` can span several lines 

## Datasets

    <datesets>
	  : <dataset>
	  | <dataset> <datasets>

    <dataset>
	  : '*dataset:' <dataset header> <data list> <dataset end>


    <dataset end>
	  : '*dataend:'
	  | '*E'

    <dataset header>
      : <dataset header lines>

    <dataset header lines>
	  : <dataset header line>
	  | <dataset header line> <dataset header lines>

    <dataset header line>
	  : '*' <dataset key-value spec>

    <dataset key-value spec>
	  : 'dscomment:' "title of dataset"
	  | 'location:' "location in paper"
	  | 'xheader:' <header specs>
	  | 'yheader:' <header specs>
	  | 'reackey:' "reaction key"
	  | 'obskey:' "observation key"
	  | 'qual:' <qualifiers>
      | 'dserror:' <common sys error spec>

    <qualifiers>
	  : <key>
	  | <key> ':' <value>

    <header specs>
	   : "header"
	   | "header" : <header specs>
	   
    <common sys error spec>
	  : <error value>
	  | <error value> : "name"

Note that `<reackey>`, `<obskey>`, `<qual>`, and `<dserror>` can be
given multiple times, while the other fields should only be given
once. 

Note that `"title of dataset"` can span several lines 

## Error values

    <error value>
	  | <two-way value>
	  | <up value> ',' <down value>

    <two-way value>
	  : "value"
	  | "value" 'PCT'
	  | '+-' "value" 
	  | '+-' "value" 'PCT'

    <up value>
	  : <sign> "value"
	  | <sign> "value" PCT

    <down value>
	  : <sign> "value"
	  | <sign> "value" PCT

    <sign>
	  : '-'
	  | '+'

Note if two error values `<up value>`and `<down value>` both are
specified then both must have the qualifier PCT or none of them can.

In principle the `<up value>` and `<down value>` can be negative and
positive respectively, indicating a possibly flip of a systematic
error. 

## data lists

    <data list>
      : 'data:' <column specs> <point list> 

    <column specs>
	  : <column spec>
	  | <column spec> ':' <column specs>

    <column spec>
	  : 'x'
	  | 'y'
	  
    <point list>
	  : <point>
	  | <point> <point list>

    <point>
	  : <x spec> ';' <y specs>

    <x spec>
	  : <bin spec>
	  | "x-value" <error value>

    <bin spec>
	  : "low" 'TO' "high"
	  | "x-value" '(BIN="low value" TO "high value" ')'

    <y specs>
	  : <y spec>
	  | <y spec> <y specs>


    <y spec>
	  : "value" ';'
	  | "value" <error value> ';'
	  | "value" <error value> '(' <sys error specs> ');'

    <sys error specs>
	  : <sys error spec>
	  | <sys error spec> ',' <sys error specs>

    <sys error spec>
	  : 'DSYS=' <error value>


## Other comments


<!-- Local Variables: -->
<!--   mode: markdown -->
<!-- End: -->


	  
    
