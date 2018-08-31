#/usr/bin/env python3
# -*- coding: utf-8 -*-

from tkinter import *
#from tkinter.ttk import *
    
# 使用eval 函数计算
def calculate():
    try:
        content = display.get()
        result = eval(content)
        display.set(content + '=\n' + str(result))
    except:
        display.set('Error')

def frame(master):
    '''将共同的属性作为默认值，以简化Frame创建过程'''
    w = Frame(master)
    w.pack(side=TOP, expand=YES, fill=BOTH)
    return w
    
def button(master, text, command, fg=None):
    '''提取共同的属性作为默认值，使Button创建过程简化'''
    w = Button(master, text=text, command=command, fg=fg, width=6)
    w.pack(side=LEFT, expand=YES, fill=BOTH, padx=2, pady=2)
    return w

def main():
    # 定义主窗口
    root = Tk()
    root.title('简易计算器')
    # 将display定义成global，main()函数外的calculate()等可以调用
    global display
    display = StringVar()
    
    # 设置内容显示栏，使用label，anchor是靠右，默认居中
    label = Label(root, relief = 'flat', borderwidth = 25, anchor = SE, width=20, background="grey", textvariable=display)
    #label = Label(root, relief = 'sunken', borderwidth = 30, anchor = SE, width=20, height=4, background="grey", textvariable=display)

    label.pack(side=TOP, expand=YES, fill=BOTH, padx=2, pady=4)

    # 添加各个按钮，并绑定行为,使用lambda很方便
    fedit = frame(root)
    button(fedit, 'C', lambda t=display:t.set(''),'#EF7321')
    button(fedit, 'DEL', lambda t=display:t.set(str(t.get()[:-1])))
    
    # 每行四个，创建其余四行按钮
    for key in ('789/', '456*', '123-', '0.=+'):
        fsymb = frame(root)
        for char in key:
            if char == '=':
                button(fsymb, char, lambda:calculate(), '#EF7321')
            else:
                button(fsymb, char, lambda t=display, c=char:t.set(t.get()+c))
    root.mainloop()
    
if __name__ == '__main__':
    main()
    
    
    
