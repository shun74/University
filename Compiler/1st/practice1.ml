let sum n =
  let rec iter i s =
    if i <= 0 then s else iter (i-1) (s+i)
in iter n 0;;
