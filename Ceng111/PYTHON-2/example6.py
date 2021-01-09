
# EXAMPLE-6

# Write a function named "translate" that performs RNA to amino acid translation.
#
#    RNA codon table is simplified to contain only five codons:
#        'UUU' -> 'Phenylalanine'
#        'UUA' -> 'Leucine'
#        'AUU' -> 'Isoleucine'
#        'GUU' -> 'Valine'
#        'UCU' -> 'Serine'
#    RNA sequence is represented as a string and its length is fixed to 15
#    The function takes one argument: RNA sequence
#    RNA sequence should start with the START codon and end with one of the STOP codons
#        START -> 'AUG'
#        STOP -> 'UAA', 'UGA' or 'UAG'
#    If the sequence does not start with the START codon, return 'start codon not recognized'
#    If the sequence does not end with the STOP codon, return 'stop codon not recognized'
#    Otherwise, the sequence is a valid RNA sequence, perform the translation and return the amino acids as a list
#
# Hints:
#
#    It is a good idea to define another function that translates a single codon into an amino acid
#    Since the length of the sequence is fixed you do not need to use recursion or iteration
#    Take a look at "list.index" function and slicing

def determine(codon):
    if codon == "UUU":
        return 'Phenylalanine'
    elif codon == "UUA":
        return 'Leucine'
    elif codon == "AUU":
        return 'Isoleucine'
    elif codon == "GUU":
        return 'Valine'
    elif codon == "UCU":
        return 'Serine'

def translate(rna):
    if rna[:3] !=  "AUG":
        return 'start codon not recognized'
    elif rna[-3:] != "UAA" and rna[-3:] != "UAG" and rna[-3:] != "UGA":
        return 'stop codon not recognized'
    else:
        return [determine(rna[3:6]),determine(rna[6:9]),determine(rna[9:12])]

# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( translate('AUGUCUGUUAUUUGA') )
# == Output ==
# ['Serine', 'Valine', 'Isoleucine']

# == Input ==
print( translate('AAAUUUUUAAUUUGA') )
# == Output ==
# 'start codon not recognized'

# == Input ==
print( translate('AUGUUUUUAAUUUGG') )
# == Output ==
# 'stop codon not recognized'

# == Input ==
print( translate('AUGUUUUUAAUUUAA') )
# == Output ==
# ['Phenylalanine', 'Leucine', 'Isoleucine']

# SOLUTION:
""" def translate(RNAseq):
    start_codon = 'AUG'
    stop_codons = ['UAA', 'UGA', 'UAG']
    if RNAseq[0:3] != start_codon:
        return 'start codon not recognized'
    if RNAseq[12:15] not in stop_codons:
        return 'stop codon not recognized'
    aminoacids = []
    aminoacids.append(translate_codon(RNAseq[3:6]))
    aminoacids.append(translate_codon(RNAseq[6:9]))
    aminoacids.append(translate_codon(RNAseq[9:12]))
    return aminoacids

def translate_codon(codon):
    codon_table = ['UUU', 'Phenylalanine', 'UUA', 'Leucine', 'AUU', 'Isoleucine', 'GUU', 'Valine', 'UCU', 'Serine']
    cIndex = codon_table.index(codon)
    return codon_table[cIndex+1] """