<h1>Comparativo das Variações do MergeSort</h1>

<p>Este projeto de comparativo de desempenho de diferentes variações do algoritmo de MergeSort. O objetivo deste estudo é analisar a performance de diferentes versões do MergeSort ao ordenar vetores de diferentes tamanhos. Abaixo, você encontrará uma explicação detalhada de cada versão implementada</p>
<ul>
  <h2>
    Variações abordadas:
  </h2>
  <li>
    MergeSort Recurtivo
  </li>
    <li>
    MergeSort Interativo
  </li>
  <li>
    MergeSort por Insercao(m)
  </li>
  <li>
    Merge Sort com Multiway Merge(k):
  </li>
</ul>
A tabela a seguir mostra os tempos de execução para diferentes tamanhos de vetor para cada algoritmo

<table border="1">
<table border="1">
  <thead>
    <tr>
      <th>Algoritmos</th>
      <th>Tamanho do vetor</th>
      <th>1000</th>
      <th>5000</th>
      <th>10000</th>
      <th>50000</th>
      <th>100000</th>
      <th>500000</th>
      <th>1000000</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>MergeSort Recursivo</td>
      <td>Tempo (segundos)</td>
      <td>0.001096s</td>
      <td>0.001772s</td>
      <td>0.002626s</td>
      <td>0.010414s</td>
      <td>0.020198s</td>
      <td>0.104404s</td>
      <td>0.211197s</td>
    </tr>
    <tr>
      <td>MergeSort Iterativo</td>
      <td>Tempo (segundos)</td>
      <td>0.001106s</td>
      <td>0.001791s</td>
      <td>0.002654s</td>
      <td>0.010003s</td>
      <td>0.020381s</td>
      <td>0.099665s</td>
      <td>0.202949s</td>
    </tr>
    <tr>
      <td>MergeSort Inserção(10)</td>
      <td>Tempo (segundos)</td>
      <td>0.001064s</td>
      <td>0.001640s</td>
      <td>0.002335s</td>
      <td>0.009048s</td>
      <td>0.017866s</td>
      <td>0.081337s</td>
      <td>0.167703s</td>
    </tr>
  </tbody>
</table>

