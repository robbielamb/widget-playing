let i = x => x;

/* let cn c => Classnames.Classname c;

   let ocn c => Classnames.Option c; */
/* let classNameReduce (baseClass: option string) (classList: list Classnames.t) => {
     let baseClass =
       switch baseClass {
       | Some name => [cn name]
       | None => []
       };
     List.rev_append baseClass classList |> Classnames.classNames
   }; */
let unwrapStr = (f, maybeStr) =>
  switch (maybeStr) {
  | Some(v) => f(v)
  | None => ""
  };
