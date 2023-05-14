import json
import random

# pijace ki so na standu
drinks = ["whiskey", "coca-cola", "rum", "juice", "jack-daniels", "ice"]

# premade cock tails
premade_drinks = {
    "Binary_Buzz": [drinks[0] + "~100" , drinks[1] + "~200", drinks[0] + "~100", drinks[3]+ "~100"],
    "Code_Cooler": [drinks[0] + "~150", drinks[1]+ "~150", drinks[3]+ "~100", drinks[3]+ "~100"],
    "Silicon_Sipper": [drinks[2]+ "~150", drinks[0]+ "~50", drinks[3]+ "~300"],
    "Byte_Breeze": [drinks[0]+ "~100", drinks[2]+ "~100", drinks[3]+ "~100", drinks[0]+ "~200"],
    "Data_Daiquiri": [drinks[1]+ "~300", drinks[3]+ "~100", drinks[3]+ "~100"],
    "Algorithmic_Ambrosia": [drinks[2]+ "~125", drinks[1]+ "~125", drinks[3]+ "~125", drinks[0]+ "~125"],
}

def select_drinks(num_drinks):
    selected_drinks = random.sample(range(len(drinks)), num_drinks)
    return selected_drinks

def choose_and_return_drink(x):
    res_body = {}
    selected_indices = select_drinks(int(x))
    res_body['drinks'] = [drinks[i] for i in selected_indices]
    return res_body

def lambda_handler(event, context):
    # get query string params input
    res_body = {}
    
    random_drink = event['queryStringParameters'].get('random', 'false')
    premade = event['queryStringParameters'].get('premade', 'false')
    izbrane_pijace = event['queryStringParameters'].get('izbrane_pijace', 'false')
    
    # poglej kaj mora vrnit in vrze use v res_body
    if random_drink != "false":
        x = event['queryStringParameters'].get('x', 4)
        res_body = choose_and_return_drink(x)
    elif premade != "false": 
        res_body['drinks'] = premade_drinks[premade]
    elif izbrane_pijace != "false":
        res_body['drinks'] = [drinks[int(s)]for s in izbrane_pijace]
        print(res_body)
    
    # craft response body
    res_body.update({'premade_drinks': premade_drinks, 'drink_choice': drinks})


    # craft http response body
    http_res = {}
    http_res['statusCode'] = 200
    http_res['headers'] = {}
    http_res['headers']['Context-Type'] = 'application/json'
    http_res['body'] = json.dumps(res_body)
    
    # by default returna premade drinke in use razlicne pijace 
    return http_res
