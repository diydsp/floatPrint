#!/usr/bin/perl



$name = "waveform_sine";


$mode=2;     # mode2 = float.   


while(<>)
{
    chomp;
    $val = $_;

    $delta[$linenum++]=$val;
}

outputCStyle();

sub outputCStyle
{
    if($mode==2){print "const char *table"."[$linenum] ={\n";}

    for($i=0;$i<$linenum;$i++){
	printf("\"");
	printf("%s", $delta[$i]);
	printf("\",");
	printf("\n");
    }
    print "};\n";

}

sub ceil
{
    my $w=shift;
    if(  ($w - int($w)) > 0){return ( int($w)+1);}
    return(int($w));
}
