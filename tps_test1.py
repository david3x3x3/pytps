import emb

def tps_test1(context, mode, args, msgid=''):
    #print('hello from python!')
    print('context = {}'.format(context))
    print('mode = {}'.format(mode))
    print('args = {}'.format(args))
    print('msgid = {}'.format(msgid))
    print('msgget = '+str(emb.msgget(msgid)))
    return '{ CONTINUE ' + msgid + ' }'
