fun subsetSumOption ([], s) =
      if s = 0 then SOME [] else NONE
  | subsetSumOption (x::xs, s) =
      (case subsetSumOption (xs, s - x) of
          SOME sol => SOME (x :: sol)
        | NONE =>
          subsetSumOption (xs, s));
