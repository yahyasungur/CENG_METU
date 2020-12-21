

# yas = int(input("Yasinizi girin:"))

# if yas >= 18:
#     print("You can enter the place.")        
# else:
#     a = 18-yas
#     print("Here is forbidden for people whose old is less than 18. See you {} years later".format(18-yas))

# note = float(input("Please enter your grade:"))

# if note >= 90:
#     print("You got AA")
#     print(note)
# elif note <90 and note >= 85:
#     print("You got BA")
#     print(note)
# elif note <85 and note >= 80:
#     print("You got BB")
#     print(note)
# else:
#     print("You failed")
#     print(note)
""" 
Yorum satırı burası

saveduser = "Ali"
username = input("Please enter your username:")

if username == saveduser:
    print("username is correct")
    password = input("Please enter your password:")
 #   password2 = input("Please confirm your passsword:") 
    if password == input("Please confirm your passsword:"):
        print("Successfully enered the program.")
    else:
        print("You are damn")
else:
    print("There is no user which has this username.") """
    
""" i = 0
    
while(i<10):
    print("i'nin değeri",i)
    i += 1
 """
 
""" defkullanici = "Yahya"
defpassword = "1234"defkullanici = "Yahya"
defpassword = "1234"
 
while(1):
    user = input("Please enter your username:")
    password = input("Please enter your password:")
    
    if(defkullanici == user and defpassword == password):
        print("Wolcome...")
        break
    elif(defkullanici != user and defpassword == password):
        print("Please check your username.")
    elif(defkullanici == user and defpassword != password):
        print("Please check your password.")
        print("Do you want to change your passsword ? Y/N")
        if(input() == 'Y'):
            defpassword = input("Please enter your new password:")
            print("Password is succesfully changed...")
        else:
            print("Try again...")
    else:
        print("Try again. User is not found.")
    print("----------------------")

 
while(1):
    user = input("Please enter your username:")
    password = input("Please enter your password:")
    
    if(defkullanici == user and defpassword == password):
        print("Wolcome...")
        break
    elif(defkullanici != user and defpassword == password):
        print("Please check your username.")
    elif(defkullanici == user and defpassword != password):
        print("Please check your password.")
        print("Do you want to change your passsword ? Y/N")
        if(input() == 'Y'):
            defpassword = input("Please enter your new password:")
            print("Password is succesfully changed...")
        else:
            print("Try again...")
    else:
        print("Try again. User is not found.")
    print("----------------------")
 """
""" a = 1
for i in range(1,int(input())+1):
    a *= i
print(a) """

""" def sign_up(name = "No info...",surname = "No info.def sign_up(name = "No info...",surname = "No info...",year = "No info...",profession = "No info..."):
    print("Nanme: {} Surname: {} Year: {} Profession: {}".format(name,surname,year,profession))
    
sign_up(input(),input(),profession= input())..",year = "No info...",profession = "No info..."):
    print("Nanme: {} Surname: {} Year: {} Profession: {}".format(name,surname,year,profession))
    
sign_up(input(),input(),profession= input()) """

def f(n):
    return g(n)+g(n+2)
def g(n,counter = [0]):
    counter[0] += 1
    print(counter)
    if n<=1:
        return n
    else:
        return g(n-1)+g(n-2)
    
print(f(3))
