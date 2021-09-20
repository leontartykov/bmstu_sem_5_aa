import random
import string 
def generate_random_string(chars = string.ascii_uppercase + string.digits, N=10):
    return ''.join(random.choice(chars) for _ in range(N))