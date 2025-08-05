import numpy as np
import scipy.signal as signal

# Parâmetros do Boost
Vin = 12            # Tensão de entrada (V)
L = 1e-3          # Indutância (H)
C = 10e-6           # Capacitância (F)
R = 10              # Carga resistiva (Ohms)
fs = 10e3           # Frequência de chaveamento (Hz)
Ts = 1/fs           # Período de amostragem (s)

# Função de transferência contínua: G(s) = Vin / (L*C*s^2 + (R/L)*s)
num_ct = [Vin]
den_ct = [L*C, R, 0]

# Discretização com método bilinear
system_dt = signal.cont2discrete((num_ct, den_ct), Ts, method='bilinear')
b = system_dt[0].flatten()  # Numerador
a = system_dt[1].flatten()  # Denominador

# Arredondar para 8 casas e formatar com 'f'
b = np.round(b, 8)
a = np.round(a, 8)

# Gerar coeficientes
print(f"B0 {b[0]:.8f}f")
print(f"B1 {b[1]:.8f}f")
print(f"B2 {b[2]:.8f}f")
print(f"A1 {a[1]:+.8f}f")
print(f"A2 {a[2]:+.8f}f")
