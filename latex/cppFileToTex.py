'''
Author: winterzz1 1002658987@qq.com
Date: 2023-10-18 00:28:21
LastEditors: winterzz1 1002658987@qq.com
LastEditTime: 2023-10-18 01:48:47
FilePath: /chino-acm-template/latex/cppFileToTex.py
Description: tex脚本
'''
import sys
import os

class tex_section:
    def __init__(self,description,path) -> None:
        self.description = description
        self.path = path
    def to_string(self) -> None:
        return '\\subsubsection{'+self.description+'}\n\\lstinputlisting[language=C++]{'+self.path+'}\n\\newpage\n'
    
def get_description(path):
    f = open(path,'r', encoding='utf-8')
    list=f.readlines()
    for i in list:
        pos=i.find('@Description:')
        if pos!=-1:
            return i[pos+len('@Description:'):].strip()
    return "未知模板"


template_begin='\\documentclass[../main.tex]{subfiles} % 使用 subfiles 文档类，指定主文档\n\\begin{document}\n'
template_end='\\end{document}'
if __name__ == '__main__':
    script_path = os.path.split(os.path.realpath(__file__))[0]
    dst_path = script_path + "/../template"
    print(dst_path)
    for sub_folder in os.listdir(dst_path):
        sub_path=dst_path + "/" + sub_folder
        if os.path.isdir(sub_path):
            if not os.path.exists(script_path+"/"+sub_folder):
                os.mkdir(script_path+"/"+sub_folder)
            f = open(script_path+"/"+sub_folder+"/"+sub_folder+".tex",'w', encoding='utf-8')
            f.write(template_begin)
            for file in os.listdir(sub_path):
                if file.endswith('.h') or file.endswith('.cpp') or file.endswith('.c'):
                    sec=tex_section(get_description(sub_path+'/'+file),'../template/'+sub_folder+'/'+file)
                    f.write(sec.to_string())
            f.write(template_end)
            f.close()