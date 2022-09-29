"""
Author: Yanrui Hu
Date: 2022-9-29
Description: Encrypt the sensitive message.
Keyword: encryption, str-process
Reason: HouLaoShi is a person who takes special message seriously.
Version: 0.0.2
"""
import random


def encrypt_message(msg: str, key: int = 0x3f) -> str:
    encrypted_msg = [chr(ord(ch) + key) for ch in msg] + ["$", str(key)]
    return "".join(encrypted_msg)


def decipher_message(encrypted_msg: str):
    lis = encrypted_msg.split("$")
    key_len = len(lis[-1])
    key = int(lis[-1])

    msg_len = len(encrypted_msg) - 1 - key_len
    original_msg = [chr(ord(ch) - key) for ch in encrypted_msg[:msg_len]]
    return "".join(original_msg)


if __name__ == "__main__":
    msg = "侯老师，你知道这句话是什么意思吗？"
    key = random.randint(0x3f, 0xf3)
    print(encrypt_message(msg, key))

    enc_msg = input()
    print(decipher_message(encrypted_msg=enc_msg))
