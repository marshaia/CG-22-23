# [LEI] - Computação Gráfica - Fase **1**

## **Grupo 30:**
- Maria Cunha - A93264
- Joana Alves - A93290
- Vicente Moireia - A93296


## **Instruções de Build:**

Utilizar a ferramenta _CMake_ para gerar o executável quer da aplicação generator, quer do engine. Depois de configurado e gerado, só necessita do comando _make_ na build gerada.

### **Generator**

Para a utilização genérica do generator, execute o comando:

```
./generator [SHAPE] [PARAMETERS] [FILE]
```

Em caso de erros, o generator irá providenciar instruções mais detalhadas (Para obter as intruções pode-se invocar apenas "./generator")

### **Engine**

Para a utilização do engine só é necessário fornecer um XML de configuração e executa-lo com:

```
./engine [XML_FILE]
```

**Nota:** A aplicação não será executada se não for fornecido este ficheiro.

### **Demo**

Depois do executável engine gerado, mova este para a pasta demo e execute:

```
./engine test.xml
```
